#include "Airport.cpp"
#include <string>
#include <list>
#include <vector>
using namespace std;

class Node
{
    private:
        Airport state;
        Node* ptr_parent;
    public:
        Node(Airport state, Node parent);
        Node(Airport state);
        vector<Airport> solution_path();
        Airport get_node_state();
        Node get_parent_node();
        string to_string();
        bool operator == (const Node &rhs) const;

};