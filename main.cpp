#include "Graph.cpp"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


//-----------------------------     function declarations       -----------------------------//
Graph create_graph();
vector<string> create_line_vector();
vector<string> get_airportIDs();
vector<string> find_route(Airport sourceID, Airport destID);
vector<vector <string>> get_input(string filename);
void output(string filename);
string lowercase(string word);


//-----------------------------     variable declarations       -----------------------------//

// Stores Airport IDs to reference Aiport objects
unordered_map<string, Airport> names;

//-----------------------------     function defintion          -----------------------------//

// Creates a vector from a string with each 
// element being made by comma separation 
vector<string> create_line_vector(string line){
    stringstream ss(line);
    string word;
    vector<string> output;
    while(getline(ss, word, ',')){
        output.push_back(word);
    };
    return output;
};

// creates a graph to allow BFS to be used
Graph create_graph()
{
    vector<string> airport_data;
    vector<string> routes_data;
    string routes_line;
    string airport_line;
    Graph graph;
    ifstream airport_file("airports.csv");
    ifstream routes_file("routes.csv");

        // Adds Airports to the graph
        while(getline(airport_file, airport_line)){
            airport_data = create_line_vector(airport_line);
            Airport temp_airport = Airport(airport_data[0], airport_data[1], airport_data[2],
                                           airport_data[3], airport_data[4]);              
            graph.add_node(temp_airport);
            names[temp_airport.get_airportID()] = temp_airport; // Storing Airport object references
        };
    
    // Add edges to the graph
    while(getline(routes_file, routes_line)){
        routes_data = create_line_vector(routes_line);
        Airport start_airport = names[routes_data[3]];
        Airport dest_airport = names[routes_data[5]];
        graph.add_connection(start_airport, dest_airport);
    };
  
    routes_file.close();
    airport_file.close();
    return graph;
};

// Vector of Airport IDs for countries with multiple airports
vector<string> get_airportIDs(string start_city, string start_country){
    ifstream file("airports.csv");
    vector<string> airportIDs;
    string line;
    vector<string> data_list;
    while(getline(file, line)){
        data_list = create_line_vector(line);
        if((start_city == (data_list[2])) && (start_country == data_list[3])){
            airportIDs.push_back(data_list[0]);
        };
    };
    file.close();
    return airportIDs;
};

// Returns a vector containing Airline code and Number of stops
vector<string> find_route(Airport sourceID, Airport destID)
{
    ifstream routes_file("routes.csv");
    vector<string> value;
    string line;
    vector<string> routes_data;
        while(getline(routes_file, line)){
            routes_data = create_line_vector(line);
            if(routes_data[3] == sourceID.get_airportID() && routes_data[5] == destID.get_airportID())
            {
                value.push_back(routes_data[0]);
                value.push_back(routes_data[7]);
            }
        }
      
        routes_file.close();
        return value;
};

// Returns a 2x2 vector containing
// Start City, Start Country
// Destination City, Destination Country
vector<vector<string>> get_input(string filename){
    ifstream file(filename);
    vector<string> start_location; 
    vector<string> end_location;
    string line;
    vector<vector<string>> input;
    if(file.good())
    {
        getline(file, line);
    };
    start_location = create_line_vector(line);
    if(file.good())
    {
        getline(file, line);
    };
    end_location = create_line_vector(line);
    input.push_back(start_location);
    input.push_back(end_location);
    return input;
};

// Function to find route(s) from one airport to another
void output(string filename){
    Graph graph = create_graph();
    vector<vector <string>> input = get_input(filename);
    vector<Airport> path;
    Airport start_airport;
    Airport dest_airport;

    // get Start Airport
    string start_city = input.at(0)[0];
    cout << start_city << endl;
    string start_country = input.at(0)[1];
    cout << start_country << endl;
    vector<string> start_airportIDs = get_airportIDs(start_city, start_country);

    //get Destination Airport
    string dest_city = input.at(1)[0];
    cout << dest_city << endl;
    string dest_country = input.at(1)[1];
    cout << dest_country << endl;
    vector<string> dest_airportIDs = get_airportIDs(dest_city, dest_country);

    // Looks for direct connections first
    bool is_direct = false;
    for(int i = 0; i < start_airportIDs.size(); i++)
    {
        bool break_value = false;

        for(int j = 0; j < dest_airportIDs.size(); j++){
            vector<Airport> start_airport_connections = graph.connections(names[start_airportIDs[i]]);
            if(check_vector(start_airport_connections, names[dest_airportIDs[j]])){
                is_direct = true;
                start_airport = names[start_airportIDs[i]];
                dest_airport = names[dest_airportIDs[j]];
                path = graph.bfs(names[start_airportIDs[i]], names[dest_airportIDs[j]]);
                break_value = true;
                break;
            }
        }
        if(break_value){
            break;
        }
    }

    // BFS to find connecting Airports if they aren't direct
    if(!is_direct)
    {
    bool break_value = false;
        for(int i = 0; i < start_airportIDs.size(); i++)
        {
            start_airport = names[start_airportIDs[i]];
            for(int j = 0; j <= dest_airportIDs.size()-1; j++)
            {
                dest_airport = names[dest_airportIDs.at(j)];
                path = graph.bfs(start_airport, dest_airport);
                if(!path.empty())
                {
                    break_value = true;
                    break;
                };
            };
        if(break_value){
             break;
        }
        };
    }

    // write to file
    if(!path.empty())
    {
        int flight_number = 0;
        int stop_number = 0;
        string output_text;
        string lowercase_start_city = start_city;
        string lowercase_dest_city = dest_city;
        transform(lowercase_start_city.begin(), lowercase_start_city.end(), lowercase_start_city.begin(), ::tolower);
        transform(lowercase_dest_city.begin(), lowercase_dest_city.end(), lowercase_dest_city.begin(), ::tolower);
        string name_of_file = lowercase_start_city + "-" + lowercase_dest_city + "_output.txt";
        ofstream write_file(name_of_file);

        // loops each Airport in the path list
         for(int i = 0; i < path.size() -1; i++){
            flight_number++;
            vector<string> route = find_route(names[path[i].get_airportID()], names[path[i+1].get_airportID()]);
            string airline = route[0];
            string stops = route[1];

            stop_number += stoi(stops);

            write_file << "\t" << (i+1) << ". " << airline;
            write_file << " from " << path[i].get_IATA() << " to ";
            write_file << path[i+1].get_IATA() << " " << stops << " stops" << endl; 
        }
        write_file << "Total flights: " << flight_number << endl;
        write_file << "Total additional stops: " << stop_number;
        write_file.close();
    }else{
        cout << "No path found" << endl;
    }
};

    

int main(){
    output("Input.txt");
    return 0;
};