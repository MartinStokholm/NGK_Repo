#include <iostream>

#include <restinio/all.hpp>

#include <json_dto/pub.hpp>

// used in weather_data_t
struct place_t 
{
	place_t() = default;
	
	place_t(std::string placeName, std::string lat, std::string lon) 
			: m_placeName{std::move( placeName ) }
			, m_lat{std::move( lat )}
		    , m_lon{std::move( lon )}
	{}

	template<typename JSON_IO>
	void
	json_io(JSON_IO &io)
	{
		io
			& json_dto::mandatory( "placeName", m_placeName )
			& json_dto::mandatory( "lat"	  , m_lat 		)
			& json_dto::mandatory( "lon"	  , m_lon 		);
	}	

	std::string m_placeName;
	std::string m_lat;
	std::string m_lon;
};

struct weather_data_t 
{
	weather_data_t() = default;
	
	weather_data_t(std::string id, std::string date, std::string timeOfEntry, 
					place_t place, std::string temp, std::string rh)
		:	m_id{std::move( id ) } 	
		,   m_date{std::move( date ) }
		,   m_time{std::move( timeOfEntry ) }
		,	m_place{std::move( place ) }
		, 	m_temp{std::move( temp ) }
		,	m_rh{std::move( rh ) }
	{}

	template<typename JSON_IO>
	void
	json_io(JSON_IO &io)
	{
		io
			& json_dto::mandatory( "ID"   		, m_id   )
			& json_dto::mandatory( "Date" 		, m_date )
			& json_dto::mandatory( "Time" 		, m_time )
			& json_dto::mandatory( "Place"		, m_place)
			& json_dto::mandatory( "Temperature", m_temp )
			& json_dto::mandatory( "Humidity"	, m_rh 	 );
	}

	std::string m_id;
	std::string m_date;
	std::string m_time;
	place_t m_place;
	std::string m_temp;
	std::string m_rh;
};

using weather_data_collection_t = std::vector<weather_data_t>;

namespace rr = restinio::router;

using router_t = rr::express_router_t<>;

class weather_data_handler_t
{
public :
	explicit weather_data_handler_t(weather_data_collection_t & weather_data)
		:	m_weather_data(weather_data)
	{}

	weather_data_handler_t(const weather_data_handler_t &) = delete;
	weather_data_handler_t(weather_data_handler_t &&) = delete;

	auto on_weather_data_list(const restinio::request_handle_t& req, rr::route_params_t) const
	{
		auto resp = init_resp(req->create_response());

		resp.set_body("Weather Data collection (weather data count: " +
				std::to_string(m_weather_data.size()) + ")\n" );

		for(std::size_t i = 0; i < m_weather_data.size(); ++i)
		{
			resp.append_body(std::to_string(i + 1) + ". ");
			const auto & wd = m_weather_data[i];
			resp.append_body(wd.m_id + ", " + wd.m_date + ", " + wd.m_time + ", " + 
							 wd.m_place.m_placeName + ", " + wd.m_place.m_lon + ", " + 
							 wd.m_place.m_lat + ", " +  wd.m_temp + ", " + wd.m_rh   + "\n");
		}

		return resp.done();
	}

	auto on_weather_data_get(const restinio::request_handle_t& req, rr::route_params_t params)
	{
		const auto weatherDataNum = restinio::cast_to<std::uint32_t>(params["weatherDataNum"]);

		auto resp = init_resp(req->create_response());

		if(0 != weatherDataNum && weatherDataNum <= m_weather_data.size())
		{
			const auto & wd = m_weather_data[weatherDataNum - 1];
			resp.set_body("weatherData #" + std::to_string(weatherDataNum) + " is: " + 
					wd.m_id + ", " + wd.m_date + ", " + wd.m_time + ", " +
					wd.m_place.m_placeName + ", " + wd.m_place.m_lon + ", " + 
					wd.m_place.m_lat + ", " + wd.m_temp + ", " + wd.m_rh + "\n");

		}
		else
		{
			resp.set_body("No weatherData with #" + std::to_string(weatherDataNum) + "\n" );
		}

		return resp.done();
	}

	auto on_author_get(const restinio::request_handle_t& req, rr::route_params_t params)
	{
		auto resp = init_resp(req->create_response());
		try
		{
			auto id = restinio::utils::unescape_percent_encoding(params["ID"]);

			resp.set_body("WeatherData from " + id + ":\n");

			for(std::size_t i = 0; i < m_weather_data.size(); ++i)
			{
				const auto & wd = m_weather_data[i];
				if(id == wd.m_id)
				{
					resp.append_body(std::to_string(i + 1) + ". ");
					resp.append_body(wd.m_id + ", " + wd.m_date + ", " + wd.m_time + ", " + 
									 wd.m_place.m_placeName + ", " + wd.m_place.m_lon + ", " + 
									 wd.m_place.m_lat + ", " +  wd.m_temp + ", " + wd.m_rh  + "\n");
				}
			}
		}
		catch(const std::exception &)
		{
			mark_as_bad_request(resp);
		}

		return resp.done();
	}

	auto on_new_weather_data(const restinio::request_handle_t& req, rr::route_params_t)
	{
		auto resp = init_resp(req->create_response());

		try
		{
			m_weather_data.emplace_back(json_dto::from_json<weather_data_t>(req->body()));
		}
		catch( const std::exception & /*ex*/ )
		{
			mark_as_bad_request(resp);
		}

		return resp.done();
	}

	auto on_weather_data_update(const restinio::request_handle_t& req, rr::route_params_t params)
	{
		const auto weatherDataNum = restinio::cast_to<std::uint32_t>(params["weatherDataNum"]);

		auto resp = init_resp(req->create_response());

		try
		{
			auto wd = json_dto::from_json<weather_data_t>(req->body());

			if(0 != weatherDataNum && weatherDataNum <= m_weather_data.size())
			{
				m_weather_data[weatherDataNum - 1] = wd;
			}
			else
			{
				mark_as_bad_request(resp);
				resp.set_body("No weatherData with #" + std::to_string(weatherDataNum) + "\n");
			}
		}
		catch( const std::exception & /*ex*/ )
		{
			mark_as_bad_request(resp);
		}

		return resp.done();
	}

	auto on_weather_data_delete(const restinio::request_handle_t& req, rr::route_params_t params)
	{
		const auto weatherDataNum = restinio::cast_to<std::uint32_t>(params["weatherDataNum"]);

		auto resp = init_resp(req->create_response());

		if(0 != weatherDataNum && weatherDataNum <= m_weather_data.size())
		{
			const auto & wd = m_weather_data[ weatherDataNum - 1 ];
			resp.set_body("Delete weatherData #" + std::to_string(weatherDataNum) + ": " +
					wd.m_id + ", " + wd.m_date + ", " + wd.m_time + ", " + 
					wd.m_place.m_placeName + ", " + wd.m_place.m_lon + ", " + 
					wd.m_place.m_lat + ", " + wd.m_temp + ", " + wd.m_rh  + "\n");

			m_weather_data.erase(m_weather_data.begin() + (weatherDataNum - 1 ));
		}
		else
		{
			resp.set_body(
				"No weatherData with #" + std::to_string(weatherDataNum) + "\n");
		}

		return resp.done();
	}

private :
	weather_data_collection_t & m_weather_data;

	template<typename RESP>
	static RESP
	init_resp(RESP resp)
	{
		resp
			.append_header("Server", "Weather Station Bitch")
			.append_header_date_field()
			.append_header("Content-Type", "text/plain; charset=utf-8");

		return resp;
	}

	template<typename RESP>
	static void
	mark_as_bad_request(RESP &resp)
	{
		resp.header().status_line(restinio::status_bad_request());
	}
};

auto server_handler(weather_data_collection_t & weather_data_collection) 
{
	auto router = std::make_unique<router_t>();
	auto handler = std::make_shared<weather_data_handler_t>(std::ref(weather_data_collection));

	auto by = [&](auto method) {
		using namespace std::placeholders;
		return std::bind(method, handler, _1, _2);
	};

	auto method_not_allowed = [](const auto & req, auto) {
			return req->create_response(restinio::status_method_not_allowed())
					.connection_close()
					.done();
		};

	// Handlers for '/' path.
	router->http_get( "/", by(&weather_data_handler_t::on_weather_data_list));
	router->http_post( "/", by(&weather_data_handler_t::on_new_weather_data));

	// Disable all other methods for '/'.
	router->add_handler(
			restinio::router::none_of_methods(
					restinio::http_method_get(), restinio::http_method_post()),
			"/", method_not_allowed );

	// Handler for '/author/:author' path.
	router->http_get("/author/:author", by(&weather_data_handler_t::on_weather_data_get));

	// Disable all other methods for '/author/:author'.
	router->add_handler(
			restinio::router::none_of_methods(restinio::http_method_get()),
			"/author/:author", method_not_allowed);

	// Handlers for '/:weatheDataNum' path.
	router->http_get(
			R"(/:weatherDataNum(\d+))",
			by(&weather_data_handler_t::on_weather_data_get));
	router->http_put(
			R"(/:weatherDataNum(\d+))",
			by(&weather_data_handler_t::on_weather_data_update));
	router->http_delete(
			R"(/:weatherDataNum(\d+))",
			by(&weather_data_handler_t::on_weather_data_delete));

	// Disable all other methods for '/:booknum'.
	router->add_handler(
			restinio::router::none_of_methods(
					restinio::http_method_get(),
					restinio::http_method_post(),
					restinio::http_method_delete()),
			R"(/:weatherDataNum(\d+))", method_not_allowed);

	return router;

}

// UPDATE MAIN

/*************************************************************************************************/

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
			{ "0", "20/04/2022", "18:00", {"PlaceName0", "lat0", "lon0"}, "25", "69" },
			{ "1", "21/04/2022", "19:00", {"PlaceName1", "lat1", "lon1"}, "26", "70" },
			{ "2", "22/04/2022", "20:00", {"PlaceName2", "lat2", "lon2"}, "27", "71" },
			{ "3", "23/04/2022", "21:00", {"PlaceName3", "lat3", "lon3"}, "25", "69" },
			{ "4", "24/04/2022", "22:00", {"PlaceName4", "lat4", "lon4"}, "26", "70" },
			{ "5", "25/04/2022", "23:00", {"PlaceName5", "lat5", "lon5"}, "27", "71" }
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
