#include <json_dto/pub.hpp>
#include <string>
#include <iostream>

using std::string; 
using std::move;

struct place{
    place() = default;
    place(string p, double lat, double lon):
        placeName_{std::move(p)}, lat_{std::move(lat)}, lon_{std::move(lon)}
        {}

    template <typename JSON_IO>
    
    void json_io(JSON_IO& io){
        io
            & json_dto::mandatory("PlaceName", placeName_)
            & json_dto::mandatory("Latitude", lat_)
            & json_dto::mandatory("Longitude", lon_);
    }

    string placeName_;
    double lat_;
    double lon_;
};

struct weatherRegistration{
    weatherRegistration() = default;

    weatherRegistration(int ID, string date, string time, 
    place pl, double temp, int hum) : 
    
    ID_{move(ID)}, date_{move(date)}, time_{move(time)},  place_{move(pl)}, temperature_{move(temp)}, humidity_{(move(hum))}
    {}

    template <typename JSON_IO>
    
    void json_io(JSON_IO& io){
        io
            & json_dto::mandatory("ID", ID_)
            & json_dto::mandatory("Date", date_)
            & json_dto::mandatory("Time", time_)
            & json_dto::mandatory("Place", place_)
            & json_dto::mandatory("Temperature", temperature_)
            & json_dto::mandatory("Humidity", humidity_);
    }

    int ID_;
    string date_;
    string time_;
    struct place place_; 
    double temperature_;
    int humidity_; 
};