//#include "WeatherStation.hpp"
#include "StationDataT.hpp"
#include "restinio/all.hpp"
#include "string.h"
#include <iostream>

using std::cout;
place aarhusN{"Aarhus N", 13.692, 19.438};
weatherRegistration sampleWData(1, "20211105", "12:15", aarhusN, 13.1, 70);

namespace rr = restinio::router;
using router_t = rr::express_router_t<>;

using weatherData = std::vector<weatherRegistration>;

class wDataHandler{
public:
    explicit wDataHandler(weatherData &wData) : m_wData(wData)
    {}

    wDataHandler(const wDataHandler &) = delete;
    wDataHandler(wDataHandler &&) = delete;

    auto on_post_data(const restinio::request_handle_t& req, rr:route_params_t params) const

    auto on_get_data(const restinio::request_handle_t& req, rr::route_params_t params) const
    {
        auto resp = init_resp(req->create_response());

        resp.set_body("Weather data collected: \n");

        resp.append_body("ID: " + std::to_string(m_wData[0].ID_));
        resp.append_body("\nDate: " + m_wData[0].date_);
        resp.append_body("\nTime: " + m_wData[0].time_);
        resp.append_body("\nPlace \n");
        resp.append_body("Name: " + m_wData[0].place_.placeName_);
        resp.append_body("\nLatitude: " + std::to_string(m_wData[0].place_.lat_));
        resp.append_body("\nLongitude: " + std::to_string(m_wData[0].place_.lon_));
        resp.append_body("\nTemperature: " + std::to_string(m_wData[0].temperature_));
        resp.append_body("\nHumidity: " + std::to_string(m_wData[0].humidity_));
        resp.append_body("%\n");
    

        return resp.done();
    }

private:
    weatherData m_wData;
    weatherRegistration m_sampleData;

    template <typename RESP>
    static RESP
    init_resp(RESP resp)
    {
        resp
            .append_header("Server", "Weather data collection server /v.0.2")
            .append_header_date_field()
            .append_header("Content-Type", "text/plain; charset=utf-8");

            return resp;
    }

    template <typename RESP>
    static void
    mark_as_bad_request (RESP& resp)
    {
        resp.header().status_line(restinio::status_bad_request());
    }
};

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
    router->http_get("/", by(&wDataHandler::on_get_data));

    // Disable other methods for '/'
    router->add_handler(
        restinio::router::none_of_methods(
            restinio::http_method_get(), restinio::http_method_post()),
            "/", method_not_allowed);
    return router;
}

int main(void){
    
    using namespace std::chrono;

    cout << "Main online\n";
    weatherData wData;
    wData.push_back(sampleWData);
    
    try{
        using traits_t = 
            restinio::traits_t<
                restinio::asio_timer_manager_t,
                restinio::single_threaded_ostream_logger_t,
                router_t>; 
        
        restinio::run(
            restinio::on_this_thread<traits_t>()
                .address( "localhost" )
                .request_handler( server_handler(wData))
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


