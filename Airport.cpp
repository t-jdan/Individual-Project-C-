#include "Airport.hpp"
using namespace std;

Airport::Airport(string airportID, string airport_name, string city, string country, string IATA)

{
    this->airportID = airportID;
    this->airport_name = airport_name;
    this->city = city;
    this->country = country;
    this->IATA = IATA;
};
Airport::Airport(){};
string Airport::get_airport_name(){
    return airport_name;
};
string Airport::get_airportID(){
    return airportID;
};
string Airport::get_city(){
    return city;
};
string Airport::get_country(){
    return country;
};
string Airport::get_IATA(){
    return IATA;
};
bool Airport::operator==(const Airport &rhs) const{
    return airportID == rhs.airportID;
};