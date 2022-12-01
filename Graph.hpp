#include "Node.cpp"
#include <list>
#include <vector>
#include <unordered_map>
using namespace std;

class Graph{
    private:
        int no_vertice = 0;
        unordered_map<string , vector<Airport>> graph;
    public:
        void add_node(Airport Node);
        void add_connection(Airport source_airport, Airport dest_airport);
        void remove_connection(Airport source_airport, Airport dest_airport);
        vector<Airport> bfs(Airport start_airport, Airport dest_airport);
        vector<Airport> connections(Airport airport);
        // bool check_vector(vector<Airport> vector, Airport value);
};