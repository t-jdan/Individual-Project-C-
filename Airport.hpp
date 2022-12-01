#include <string>
using namespace std;

/**
 * @brief This class constructs an Airport Object
 * which holds the attributes of an Airport
 * 
 * @author Jordan Ayiku Teye
 * 
 */

class Airport
{
    private:
        string airportID;
        string airport_name;
        string city;
        string country;
        string IATA;
        string ICAO;
        // string latitude;
        // string longitude;
        // string altitude;
        // string timezone;
        // string DST;
        // string tz;
        // string type;
        // string source;
    public:
        Airport();
        Airport(string airportID, string airport_name, string city, string country, string IATA);
        // , string ICAO, string latitude, string longitude, string altitude, string timezone, string DST, string tz, string type, string source);
        string get_airportID();
        string get_airport_name();
        string get_city();
        string get_country();
        string get_IATA();
        bool operator == (const Airport &rhs) const;
};