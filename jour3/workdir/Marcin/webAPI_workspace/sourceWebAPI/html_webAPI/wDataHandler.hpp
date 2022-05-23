#pragma once

#include "StationDataT.hpp"
#include "restinio/all.hpp"
#include <restinio/websocket/websocket.hpp>
#include <map>
#include "string.h"

namespace rr = restinio::router;
namespace rws = restinio::websocket::basic;

using router_t = rr::express_router_t<>;
using weatherData = std::vector<weatherRegistration>;
using ws_registry_t = std::map<std::uint64_t, rws::ws_handle_t>;


class wDataHandler{
public:
    explicit wDataHandler(weatherData &wData) : m_wData(wData)
    {}

    wDataHandler(const wDataHandler &) = delete;
    wDataHandler(wDataHandler &&) = delete;

    auto on_post_data(const restinio::request_handle_t& req, rr::route_params_t);
    auto on_get_data(const restinio::request_handle_t& req, rr::route_params_t params) const;
    auto on_get_all(const restinio::request_handle_t& req, rr::route_params_t params) const;
    auto on_get_three(const restinio::request_handle_t& req, rr::route_params_t params) const;
    auto on_update(const restinio::request_handle_t& req, rr::route_params_t params) const;
    auto on_live_update(const restinio::request_handle_t& req, rr::route_params_t params);
    auto options(restinio::request_handle_t req, restinio::router::route_params_t);

private:
    ws_registry_t m_registry;
    weatherData m_wData;
    weatherRegistration m_sampleData;
    void sendMessage(std::string message){
        for(auto [k,v] : m_registry)
            v-> send_message(rws::final_frame, rws::opcode_t::text_frame, message);
    }
    int append_data(restinio::response_builder_t<restinio::restinio_controlled_output_t> &resp, int i = -1) const;

    template <typename RESP>
    static RESP
    init_resp(RESP resp)
    {
        resp
            .append_header("Server", "Weather data collection server /v.0.4")
            .append_header_date_field()
            .append_header("Content-Type", "application/json")
            .append_header(restinio::http_field::access_control_allow_origin, "*");

            return resp;
    }

    template <typename RESP>
    static void
    mark_as_bad_request (RESP& resp)
    {
        resp.header().status_line(restinio::status_bad_request());
    }
};

auto server_handler(weatherData &data);

int run();