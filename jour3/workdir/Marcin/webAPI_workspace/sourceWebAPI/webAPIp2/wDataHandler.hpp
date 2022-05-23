#pragma once

#include "StationDataT.hpp"
#include "restinio/all.hpp"
#include "string.h"

namespace rr = restinio::router;
using router_t = rr::express_router_t<>;

using weatherData = std::vector<weatherRegistration>;

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

private:
    weatherData m_wData;
    weatherRegistration m_sampleData;
    int append_data(restinio::response_builder_t<restinio::restinio_controlled_output_t> &resp, int i = -1) const;

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

auto server_handler(weatherData &data);

int run();