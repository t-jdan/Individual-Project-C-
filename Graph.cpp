#include "Graph.hpp"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

void Graph::add_node(Airport Node)
{
    vector<Airport> adj_routes;
    graph.insert({Node.get_airportID(), adj_routes});
    no_vertice++;
};

// Function to check if a key exists in a graph
bool check_key(unordered_map<string, list<Airport>> graph, string key){
    bool return_value = false;
    if (graph.count(key))
    {
        return_value = true;
    };
    return return_value;
};

// Function to check if a value exists in a vector
bool check_vector(vector<string> vector, string value){
    bool return_value = false;
    if (count(vector.begin(), vector.end(), value)) {
        return_value = true;
    }
    return return_value;
}

// Function to check if a value exists in a vector consisting of Airports
bool check_vector(vector<Airport> vector, Airport value){
    bool return_value = false;
    if (count(vector.begin(), vector.end(), value)) {
        return_value = true;
    }
    return return_value;
}

void Graph::add_connection(Airport source_airport, Airport dest_airport)
{
    if(graph.count(source_airport.get_airportID())){
        if(!check_vector(graph[source_airport.get_airportID()], dest_airport)){
            graph[source_airport.get_airportID()].push_back(dest_airport);
            graph[dest_airport.get_airportID()].push_back(source_airport);
        }
    }
};
vector<Airport> Graph::connections(Airport airport){
    return graph[airport.get_airportID()];
}

vector<Airport> Graph::bfs(Airport start_airport, Airport dest_airport)
{
    Node node(start_airport);
    vector<Node> frontier;
    vector<Airport> successors;
    unordered_set<string> explored;
    vector<Airport> output;
    bool break_value = false; // Allows outer loop to be broken

    // List of Airports that are connected to the start and destination airports
    vector<Airport> start_list = graph[start_airport.get_airportID()];
    vector<Airport> end_list = graph[dest_airport.get_airportID()];
    if(check_vector(start_list, dest_airport))
    {
        // returns solution if Airports have a direct connection
        output.push_back(start_airport);
        output.push_back(dest_airport);
        cout << "direct" << endl;
    }else{

        cout << "not direct" << endl;
        if((!start_list.empty()) && (!end_list.empty())){
            frontier.push_back(node);
            while(frontier.size() > 0){
                node = frontier.front();
                frontier.erase(frontier.begin());
                explored.insert(node.to_string());
                successors = graph[node.get_node_state().get_airportID()];

                cout << "Passed stage 1" << endl;
            
                for(int i = 0; i <successors.size(); i ++){
                    Node child = Node(successors[i], node);
                    bool in_explored = (find(explored.begin(), explored.end(), child.to_string()) != explored.end());
                    bool in_frontier = (find(frontier.begin(), frontier.end(), child) != frontier.end());

                    if((!in_explored) && (!in_frontier)){
                        vector<Airport> child_list = graph[child.get_node_state().get_airportID()];
                        bool in_child_list = find(child_list.begin(), child_list.end(), dest_airport) != child_list.end();
                        
                        if(in_child_list){
                            cout << child.get_node_state().get_airportID() << endl;
                            output = child.solution_path();
                            output.push_back(dest_airport);
                            break_value = true;
                            break;
                        };
                        frontier.push_back(child);
                    };
                };
                if(break_value){
                    break;
                };
            };
        }
        return output;
    };
    if(output.empty())
    {
        cout << "No Path Found" << endl;
    }
    return output;
};
