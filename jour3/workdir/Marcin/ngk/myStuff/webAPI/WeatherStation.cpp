#include "WeatherStation.hpp"

WeatherStation::WeatherStation(){

}

WeatherStation::~WeatherStation(){
    for(weatherRegistration* item : wData){
        delete item;
    }
}