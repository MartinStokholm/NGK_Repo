#include "wDataHandler.hpp"


auto wDataHandler::on_post_data(const restinio::request_handle_t& req, rr::route_params_t params)
{
    auto resp = init_resp(req->create_response());

    try
    {
        m_wData.emplace_back(
            json_dto::from_json<weatherRegistration>(req->body()));
    }
    catch(const std::exception &)
    {
        mark_as_bad_request(resp);
    }

    return resp.done();
}

auto wDataHandler::on_get_all(const restinio::request_handle_t& req, rr::route_params_t params) const
{
    auto resp = init_resp(req->create_response());
    resp.set_body("Weather data collected: \n");
    int i = 0;
    for(weatherRegistration data : m_wData){
        append_data(resp, i);
        i++;
    }
    return resp.done();

}

int wDataHandler::append_data(restinio::response_builder_t<restinio::restinio_controlled_output_t> &resp, int i) const
{
    if(i < 0){
        return -1;
    }

    resp.append_body("ID: " + std::to_string(m_wData[i].ID_));
    resp.append_body("\nDate: " + m_wData[i].date_);
    resp.append_body("\nTime: " + m_wData[i].time_);
    resp.append_body("\nPlace \n");
    resp.append_body("Name: " + m_wData[i].place_.placeName_);
    resp.append_body("\nLatitude: " + std::to_string(m_wData[i].place_.lat_));
    resp.append_body("\nLongitude: " + std::to_string(m_wData[i].place_.lon_));
    resp.append_body("\nTemperature: " + std::to_string(m_wData[i].temperature_));
    resp.append_body("\nHumidity: " + std::to_string(m_wData[i].humidity_));
    resp.append_body("%\n\n");

    return 0;
}

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

        for(int i = 0; i < m_wData.size(); i++){
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
    router->http_get("/Date/:Date", by(&wDataHandler::on_get_data));
    router->http_get("/all", by(&wDataHandler::on_get_all));
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
        using traits_t = 
            restinio::traits_t<
                restinio::asio_timer_manager_t,
                restinio::single_threaded_ostream_logger_t,
                router_t>; 
        
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