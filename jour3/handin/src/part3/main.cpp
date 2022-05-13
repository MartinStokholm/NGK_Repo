#include <iostream>
#include <fstream>
#include <restinio/all.hpp>
#include <json_dto/pub.hpp>
#include <restinio/websocket/websocket.hpp>

// used in weather_data_t
struct place_t 
{
	place_t() = default;
	
	place_t(std::string placeName, float lat, float lon) 
			: m_placeName{std::move( placeName ) }
			, m_lat{std::move( lat )}
		    , m_lon{std::move( lon )}
	{}

	template<typename JSON_IO> void	json_io(JSON_IO &io)
	{
		io
			& json_dto::mandatory( "PlaceName", m_placeName )
			& json_dto::mandatory( "Lat"	  , m_lat 		)
			& json_dto::mandatory( "Lon"	  , m_lon 		);
	}	

	std::string m_placeName;
	float m_lat;
	float m_lon;
};

struct weather_data_t 
{
	weather_data_t() = default;
	
	weather_data_t(uint32_t id, std::string date, std::string timeOfEntry, 
					place_t place, std::string temp, std::string rh)
		:	m_id{std::move( id ) } 	
		,   m_date{std::move( date ) }
		,   m_time{std::move( timeOfEntry ) }
		,	m_place{std::move( place ) }
		, 	m_temp{std::move( temp ) }
		,	m_rh{std::move( rh ) }
	{}

	template<typename JSON_IO> void json_io(JSON_IO &io)
	{
		io
			& json_dto::mandatory( "ID"   		, m_id   )
			& json_dto::mandatory( "Date" 		, m_date )
			& json_dto::mandatory( "Time" 		, m_time )
			& json_dto::mandatory( "Place"		, m_place)
			& json_dto::mandatory( "Temperature", m_temp )
			& json_dto::mandatory( "Humidity"	, m_rh 	 );
	}

	uint32_t m_id;
	std::string m_date;
	std::string m_time;
	place_t m_place;
	std::string m_temp;
	std::string m_rh;
};

// vector list is used to store all weather_data_t entries
using weather_data_collection_t = std::vector<weather_data_t>;

namespace rr = restinio::router;
using router_t = rr::express_router_t<>;

// WebSocket specifics
namespace rws = restinio::websocket::basic;
using traits_t = restinio::traits_t<
				 restinio::asio_timer_manager_t,
				 restinio::single_threaded_ostream_logger_t,
				 router_t>;

// ws_registry_t is required to store handles to created webSockets.
using ws_registry_t = std::map<std::uint64_t, rws::ws_handle_t>;

// handler for weather data requests
class weather_data_handler_t
{
public :
	explicit weather_data_handler_t(weather_data_collection_t & weather_data)
		:	m_weather_data(weather_data)
	{}

	weather_data_handler_t(const weather_data_handler_t &) = delete;
	weather_data_handler_t(weather_data_handler_t &&) = delete;

	// sends back a response containing a html table with the data from weather_data_collection_t
	auto on_weatherData_htmlTable_get(const restinio::request_handle_t& req, rr::route_params_t) const
	{
		auto resp = init_resp(req->create_response());

		resp.append_header("Server", "WeatherStation");
		resp.append_header_date_field();
		resp.append_header(
					restinio::http_field::content_type,
					"text/html; charset=utf-8");	
		resp.set_body("<!DOCTYPE html><html><style>table, th, td {border:1px solid black;}</style><body>");
		resp.append_body("<h2>WeatherStation</h2>");

		for (auto i = m_weather_data.begin(); i != m_weather_data.end(); i++)
		{
			resp.append_body("<table style='width:100%'>");
			resp.append_body("<tr>");
			resp.append_body("<th>Field</th>");
			resp.append_body("<th>Field value</th>");
			resp.append_body("</tr>");
			resp.append_body("<tr>");
			resp.append_body("<td>ID</td>");
			resp.append_body("<td>" + std::to_string(i->m_id) + "</td>");
			resp.append_body("</tr>");
			resp.append_body("<tr>");
			resp.append_body("<td>Date</td>");
			resp.append_body("<td>" + i->m_date + "</td>");
			resp.append_body("</tr>");
			resp.append_body("<tr>");
			resp.append_body("<td>Time</td>");
			resp.append_body("<td>" + i->m_time + "</td>");
			resp.append_body("</tr>");
			resp.append_body("<tr>");
			resp.append_body("<td>PlaceName</td>");
			resp.append_body("<td>" + i->m_place.m_placeName + "</td>");
			resp.append_body("</tr>");
			resp.append_body("<tr>");
			resp.append_body("<td>Lat</td>");
			resp.append_body("<td>" + std::to_string(i->m_place.m_lat) + "</td>");
			resp.append_body("</tr>");
			resp.append_body("<tr>");
			resp.append_body("<td>Lon</td>");
			resp.append_body("<td>" + std::to_string(i->m_place.m_lon) + "</td>");
			resp.append_body("</tr>");
			resp.append_body("<tr>");
			resp.append_body("<td>Temperature</td>");
			resp.append_body("<td> " + i->m_temp + "</td>");
			resp.append_body("</tr>");
			resp.append_body("<tr>");
			resp.append_body("<td>Humidity</td>");
			resp.append_body("<td>" + i->m_rh + "</td>");
			resp.append_body("</tr></table>");
			resp.append_body("<br>");
		}
		resp.append_body("</body></html>");
		return resp.done();
	}
	
	// sends back respons containing the three newest entries from weather_data_collection_t
	auto on_weatherData_threeLatest_get(const restinio::request_handle_t& req, rr::route_params_t)         
    {                                                                                               
    	auto resp = init_resp(req->create_response());                                              
                                                                                                        
		weather_data_collection_t temp;
                                                                                                        
        const auto & wd = m_weather_data;                                                           

        if (wd.size() > 3)                                                                          
        {                                                                                           
        	for (std::size_t i = wd.size(); i > wd.size()-3;i--)                                    
            {                                                                                       
				temp.push_back(wd[i-1]);
            }                                                                                       
        }                                                                                           
        else                                                                                        
        {                                                                                           
			sendMessage("There are less than three weatherdata");
		}
		resp.set_body(json_dto::to_json<weather_data_collection_t>(temp));	
		sendMessage("GET three latest weatherdata");
        return resp.done();                                                                         
    }                                
	
	// sends back respons containing all entries from weather_data_collection_t
	auto on_weatherData_all_get(const restinio::request_handle_t& req, rr::route_params_t) 
	{
		auto resp = init_resp(req->create_response());
		const auto & wd = m_weather_data;
		resp.set_body(json_dto::to_json< std::vector<weather_data_t> >(wd));
		sendMessage("GET all weatherdata");
		return resp.done();
	}

	// sends back respons containing specific entry based on the field "date"
	auto on_weatherData_date_get(const restinio::request_handle_t& req, rr::route_params_t params)
	{
		const auto weatherDataDate = restinio::cast_to<std::string>(params["weatherDataDate"]);

		weather_data_collection_t temp;

		auto resp = init_resp(req->create_response());
		int cnt = 0;
		for(auto i = m_weather_data.begin(); i != m_weather_data.end(); i++)
		{
			if(i->m_date == weatherDataDate)
			{
				temp.push_back(m_weather_data[cnt]);
			}
			++cnt;
		}
		resp.set_body(json_dto::to_json<weather_data_collection_t>(temp));	
		sendMessage("GET weatherdata by date ");
		return resp.done();
	}

	// takes content from request body and add an entry to weather_data_collection_t
	auto on_weatherData_add(const restinio::request_handle_t& req, rr::route_params_t)
	{
		auto resp = init_resp(req->create_response());

		try
		{
			m_weather_data.emplace_back(json_dto::from_json<weather_data_t>(req->body()));
			// Will send message to webSocket that new data has been posted with ID -> m_id
			sendMessage("POST new entry added ");
		}
		catch( const std::exception & /*ex*/ )
		{
			mark_as_bad_request(resp);
			sendMessage("POST to weatherdata failed");
		}

		return resp.done();
	}
	
	// sends back respons containing specific entry based on the field "id"
	auto on_weatherData_ID_get(const restinio::request_handle_t& req, rr::route_params_t params)
	{
		const auto weatherDataID = restinio::cast_to<std::uint32_t>(params["weatherDataID"]);

		auto resp = init_resp(req->create_response());

		if(0 != weatherDataID && weatherDataID <= m_weather_data.size())
		{
			weather_data_collection_t temp;

			for(auto i = m_weather_data.begin(); i != m_weather_data.end(); i++)
			{	
				if(i->m_id == weatherDataID)
				{
					const auto & wd = m_weather_data[weatherDataID - 1];
					temp.push_back(wd);
				}
			}
			resp.set_body(json_dto::to_json<weather_data_collection_t>(temp));	
			sendMessage("GET on entry with # " + std::to_string(weatherDataID));
		}
		else
		{
			resp.set_body("No weatherData with # " + std::to_string(weatherDataID) + "\n" );
			sendMessage("No entries with # " + std::to_string(weatherDataID));
		}

		return resp.done();
	}
	
	// takes content from request body and updates an entry based on field "id"
	auto on_weatherData_ID_update(const restinio::request_handle_t& req, rr::route_params_t params)
	{
		const auto weatherDataID = restinio::cast_to<std::uint32_t>(params["weatherDataID"]);

		auto resp = init_resp(req->create_response());

		try
		{
			auto wd = json_dto::from_json<weather_data_t>(req->body());

			if(0 != weatherDataID && weatherDataID <= m_weather_data.size())
			{
				m_weather_data[weatherDataID - 1] = wd;
				sendMessage("PUT on # " + std::to_string(weatherDataID));
			}
			else
			{
				mark_as_bad_request(resp);
				resp.set_body("No weatherData with #" + std::to_string(weatherDataID) + "\n");
				sendMessage("No entry with # " + std::to_string(weatherDataID));
			}
		}
		catch( const std::exception & /*ex*/ )
		{
			mark_as_bad_request(resp);
		}

		return resp.done();
	}

	// deletes entry from weather_data_collection_t based on field "id"
	auto on_weatherData_ID_delete(const restinio::request_handle_t& req, rr::route_params_t params)
	{
		const auto weatherDataID = restinio::cast_to<std::uint32_t>(params["weatherDataID"]);

		auto resp = init_resp(req->create_response());

		if(0 != weatherDataID && weatherDataID <= m_weather_data.size())
		{
			const auto & wd = m_weather_data[ weatherDataID - 1 ];
			resp.set_body("Delete weatherData #" + std::to_string(weatherDataID) + "\n");
			resp.append_body(json_dto::to_json(wd));

			m_weather_data.erase(m_weather_data.begin() + (weatherDataID - 1 ));
			sendMessage("DELETE entry # " + std::to_string(weatherDataID));
		}
		else
		{
			resp.set_body("No weatherData with #" + std::to_string(weatherDataID) + "\n");
			sendMessage("No entry with # " + std::to_string(weatherDataID));
		}

		return resp.done();
	}

	// creates webSocket handler, stores client info in registry
	auto on_live_update(const restinio::request_handle_t& req, rr::route_params_t params)
	{
		// check if the request is an upgrade connection type aka webSocket
		if (restinio::http_connection_header_t::upgrade == req->header().connection())
		{
			// create webSocket handler
			auto wsh = rws::upgrade<traits_t>(*req, rws::activation_t::immediate, [this](auto wsh, auto m)
			{
				if( rws::opcode_t::text_frame == m->opcode() ||
					rws::opcode_t::binary_frame == m->opcode() ||
					rws::opcode_t::continuation_frame == m->opcode() )
				{
					wsh->send_message( *m );
				}
				else if( rws::opcode_t::ping_frame == m->opcode() )
				{
					auto resp = *m;
					resp.set_opcode( rws::opcode_t::pong_frame );
					wsh->send_message( resp ); 
				}
				else if( rws::opcode_t::connection_close_frame == m->opcode() )
				{
					m_registry.erase( wsh->connection_id() );
				}	
			});
			m_registry.emplace(wsh->connection_id(), wsh);
			init_resp(req->create_response()).done();
			return restinio::request_accepted();
		}
		return restinio::request_rejected();
	}  

	// function for options needed for webSocket, and to enable CORS
	auto options(restinio::request_handle_t req, restinio::router::route_params_t)
	{
		const auto methods = "OPTIONS, GET, POST, PATCH, DELETE, PUT";
		auto resp = init_resp(req->create_response());
		resp.append_header(restinio::http_field::access_control_allow_methods, methods);
		resp.append_header(restinio::http_field::access_control_allow_headers, "content-type");
		resp.append_header(restinio::http_field::access_control_max_age, "86400");
		return resp.done();
	}

private :
	// vector list of struct weather_data_t holds all server data
	weather_data_collection_t & m_weather_data;

	// webSocket registry holds information about clients that are connected
	ws_registry_t m_registry;

	template<typename RESP>	static RESP	init_resp(RESP resp)
	{
		resp
			.append_header("Server", "Weather Station Bitch")
			.append_header_date_field()
			.append_header("Content-Type", "text/plain; charset=utf-8")
			.append_header(restinio::http_field::access_control_allow_origin, "*");
		return resp;
	}

	template<typename RESP>	static void	mark_as_bad_request(RESP &resp)
	{
		resp.header().status_line(restinio::status_bad_request());
	}

	// function for sending messages on webSocket
	void sendMessage(std::string message)
	{
		for(auto [k, v] : m_registry)
		v->send_message(rws::final_frame, rws::opcode_t::text_frame, message);	
	}
};

// Server handler function for routing
auto server_handler(weather_data_collection_t & weather_data_collection) 
{
	auto router = std::make_unique<router_t>();
	auto handler = std::make_shared<weather_data_handler_t>(std::ref(weather_data_collection));

	auto by = [&](auto method) 
	{
		using namespace std::placeholders;
		return std::bind(method, handler, _1, _2);
	};

	auto method_not_allowed = [](const auto & req, auto) 
	{
			return req->create_response(restinio::status_method_not_allowed())
					.connection_close()
					.done();
	};

	// webSocket routing
	router->http_get("/api/chat", by(&weather_data_handler_t::on_live_update));

	// get all entries from weater_data_collection_t 
	router->http_get("/api/weatherData", by(&weather_data_handler_t::on_weatherData_all_get));

	// post a entry to weather_data_collection_t 
	router->http_post("/api/weatherData", by(&weather_data_handler_t::on_weatherData_add));

	// get latest three entries from weather_data_collection_t
	router->http_get("/api/weatherData/threeLatest", by(&weather_data_handler_t::on_weatherData_threeLatest_get));

	// get the entries as a html table from weather_data_collection_t 
	router->http_get("/api/weatherData/Table", by(&weather_data_handler_t::on_weatherData_htmlTable_get));

	// get entries based on date from weatherDataCollection 
	router->http_get("/api/weatherData/date/:weatherDataDate", by(&weather_data_handler_t::on_weatherData_date_get));

	// get one entry based on index in vector list from weather_data_collection_t
	router->http_get(R"(/api/weatherData/id/:weatherDataID(\d+))", by(&weather_data_handler_t::on_weatherData_ID_get));

	// put one entry based on index in vector list from weather_data_collection_t
	router->http_put(R"(/api/weatherData/id/:weatherDataID(\d+))", by(&weather_data_handler_t::on_weatherData_ID_update));

	// delet one entry based on index in vector list from weather_data_collection_t
	router->http_delete(R"(/api/weatherData/id/:weatherDataID(\d+))",	by(&weather_data_handler_t::on_weatherData_ID_delete));
	
	// options routing for CORS
	router->add_handler(restinio::http_method_options(), "/api/weatherData/date/:weatherDataDate", by(&weather_data_handler_t::options));
	router->add_handler(restinio::http_method_options(), "/api/weatherData/id/:weatherDataID", by(&weather_data_handler_t::options));
	router->add_handler(restinio::http_method_options(), "/api/weatherData", by(&weather_data_handler_t::options));
	router->add_handler(restinio::http_method_options(), "/api/weatherData/threeLatest", by(&weather_data_handler_t::options));

	return router;
}

int main()
{
	using namespace std::chrono;
	
	try
	{
		using traits_t =
			restinio::traits_t<
				restinio::asio_timer_manager_t,
				restinio::single_threaded_ostream_logger_t,
				router_t >;

		weather_data_collection_t weather_data_collection{
			{ 1, "20211105", "12:15", {"Aarhus N", 13.692, 19.438}, "13.1", "70%" },
			{ 2, "20211105", "12:15", {"Aarhus N", 13.692, 19.438}, "14.1", "69%" },
			{ 3, "20221105", "12:15", {"Aarhus N", 13.692, 19.438}, "15.1", "42%" },
			{ 4, "20231105", "12:15", {"Aarhus N", 13.692, 19.438}, "16.1", "17%" },
		}; 	


		restinio::run(
			restinio::on_this_thread< traits_t >()
				.address( "localhost" )
				.request_handler( server_handler(weather_data_collection))
				.read_next_http_message_timelimit(10s)
				.write_http_response_timelimit(1s)
				.handle_request_timeout(1s));
	}
	catch(const std::exception & ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
