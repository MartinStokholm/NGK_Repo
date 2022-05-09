#include <restinio/all.hpp>
#include <vector>
#include "StationDataT.hpp"

using std::vector;

class WeatherStation{
public:
    WeatherStation();
    ~WeatherStation();

private:
    vector<weatherRegistration*> wData;
};

