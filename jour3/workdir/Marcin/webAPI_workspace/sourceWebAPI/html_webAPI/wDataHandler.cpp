#include "wDataHandler.hpp"

// Updated to use websockets!

using traits_t = 
            restinio::traits_t<
                restinio::asio_timer_manager_t,
                restinio::single_threaded_ostream_logger_t,
                router_t>; 

auto wDataHandler::on_post_data(const restinio::request_handle_t& req, rr::route_params_t params)
{
    auto resp = init_resp(req->create_response());

    try
    {
        m_wData.emplace_back(
            json_dto::from_json<weatherRegistration>(req->body()));

        sendMessage("POST: id = " + json_dto::from_json<weatherRegistration>(req->body()).ID_);
    }
    catch(const std::exception &)
    {
        mark_as_bad_request(resp);
    }

    return resp.done();
}

auto wDataHandler::on_live_update(const restinio::request_handle_t& req, rr::route_params_t params){
    if(restinio::http_connection_header_t::upgrade == req->header().connection())
    {
        printf("Received ws upgrade request\n");
        auto wsh = rws::upgrade<traits_t>(*req, rws::activation_t::immediate,
        [this](auto wsh, auto m){
            if(rws::opcode_t::text_frame == m->opcode() ||
                rws::opcode_t::binary_frame == m->opcode() ||
                rws::opcode_t::continuation_frame == m->opcode())
                {
                    printf("3 opcode frames, sending message\n");
                    wsh->send_message(*m);
                }
                else if(rws::opcode_t::ping_frame == m->opcode())
                {
                    auto resp = *m;
                    resp.set_opcode(rws::opcode_t::pong_frame);
                    wsh->send_message(resp);
                }
                else if(rws::opcode_t::connection_close_frame == m->opcode())
                {
                    m_registry.erase(wsh->connection_id());
                }
        });

        m_registry.emplace(wsh->connection_id(), wsh);

        init_resp(req->create_response()).done();

        return restinio::request_accepted();
    }
    return restinio::request_rejected();
}

// Unimplemented options , PATCH, DELETE, PUT
auto wDataHandler::options(restinio::request_handle_t req, restinio::router::route_params_t){
    const auto methods = "OPTIONS, GET, POST";
    auto resp = init_resp(req->create_response());
    resp.append_header(restinio::http_field::access_control_allow_methods, methods);
    resp.append_header(restinio::http_field::access_control_allow_headers, "content-type");
    resp.append_header(restinio::http_field::access_control_max_age, "86400");
    return resp.done();
}

// Returns data from 3 latest weather registrations
auto wDataHandler::on_get_three(const restinio::request_handle_t& req, rr::route_params_t params) const{
    auto resp = init_resp(req->create_response());

    if(m_wData.empty()){
        resp.set_body("No weather data on the server!\n");
        return resp.done();
    }

    resp.set_body("Weather data from last 3 measurements: \n\n");
    unsigned int i = m_wData.size() - 1;
    for(i; i > m_wData.size() - 4; i--){
        append_data(resp, i);
    }
    return resp.done();
}

// Returns data from all weather registrations in the system
auto wDataHandler::on_get_all(const restinio::request_handle_t& req, rr::route_params_t params) const
{
    auto resp = init_resp(req->create_response());
    if(m_wData.empty()){
        //resp.set_body("No weather data on the server!\n");
        return resp.done();
    }

    // resp.set_body("All weather data collected: \n\n");
    resp.append_body(json_dto::to_json<weatherRegistration>(m_wData[0]));
    return resp.done();

}

// Appends a weather registration data from registered data vector chosen by index
int wDataHandler::append_data(restinio::response_builder_t<restinio::restinio_controlled_output_t> &resp, int i) const
{

    if(i < 0){
        return -1;
    }

    resp.append_body(json_dto::to_json<weatherRegistration>(m_wData[i]));
    return 0;
}

// Returns all weather data from a specific date
auto wDataHandler::on_get_data(const restinio::request_handle_t& req, rr::route_params_t params) const
{
    auto resp = init_resp(req->create_response());
    if(m_wData.empty()){
        resp.set_body("No weather data on the server!\n");
        return resp.done();
    }
    
    try{
        auto date = restinio::utils::unescape_percent_encoding(params["Date"]);

        resp.set_body("Weather data for the selected date: \n");

        for(unsigned int i = 0; i < m_wData.size(); i++){
            if(date == m_wData[i].date_){
                append_data(resp, i);
            }
        }
    }
    catch(const std::exception &)
    {
        mark_as_bad_request(resp);
    }
    return resp.done();
}


// Binds the handler functions to HTTP requests!
auto server_handler(weatherData &data)
{
    auto router = std::make_unique<router_t>();
    auto handler = std::make_shared<wDataHandler>(std::ref(data));

    auto by = [&] (auto method){
        using namespace std::placeholders;
        return std::bind(method, handler, _1, _2);
    };

    auto method_not_allowed = [] (const auto & req, auto){
        return req->create_response(restinio::status_method_not_allowed())
            .connection_close()
            .done();
    };

    // Handler for '/' path
    router->add_handler(restinio::http_method_options(), "/", by(&wDataHandler::options));
    router->http_get("/chat", by(&wDataHandler::on_live_update));
    router->http_get("/Date/:Date", by(&wDataHandler::on_get_data));
    router->http_get("/lastThree", by(&wDataHandler::on_get_three));
    router->http_get("/all", by(&wDataHandler::on_get_all));
    router->http_get("/", by(&wDataHandler::on_get_all));
    router->http_post("/", by(&wDataHandler::on_post_data));
    
    
    // Disable other methods for '/'
    router->add_handler(
        restinio::router::none_of_methods(
            restinio::http_method_get(), restinio::http_method_post()),
            "/", method_not_allowed);
    return router;
}

int run(){
    using namespace std::chrono;
    
    weatherData wData;
    
try{    
        restinio::run(
            restinio::on_this_thread<traits_t>()
                .address( "localhost" )
                .request_handler(server_handler(wData))
                .read_next_http_message_timelimit( 10s )
                .write_http_response_timelimit( 1s )
                .handle_request_timeout( 1s )
        );
    }
    catch( const std::exception & ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}