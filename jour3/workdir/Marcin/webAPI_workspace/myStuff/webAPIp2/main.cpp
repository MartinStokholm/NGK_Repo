//#include "WeatherStation.hpp"
#include "wDataHandler.hpp"
#include <iostream>

using std::cout;
place aarhusN{"Aarhus N", 13.692, 19.438};
weatherRegistration sampleWData(1, "20211105", "12:15", aarhusN, 13.1, 70);

int main(void){

    cout << "Main online\n";
    
    //wDataHandler handler;
    

    return run();
}


