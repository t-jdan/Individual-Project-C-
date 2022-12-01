#include "Node.hpp"
#include <list>
#include <bits/stdc++.h>
using namespace std;

Node::Node(Airport state, Node parent)
{
    this->state = state;
    this->ptr_parent = &parent;
};
Node::Node(Airport state)
{
    this->state = state;
    this->ptr_parent = nullptr;
}
Airport Node::get_node_state(){
    return state;
};
Node Node::get_parent_node(){
    return *ptr_parent;
}
string Node::to_string(){
    return state.get_airportID();
}
bool Node::operator==(const Node &rhs) const{
    return state == rhs.state;
};
vector<Airport> Node::solution_path()
{
    vector<Airport> path;
    path.push_back(this->state);
        Node parent_node = ptr_parent->get_node_state();
   
    while(&parent_node != nullptr){
        Airport parent_state = parent_node.get_node_state();
        path.push_back(parent_state);
        parent_node = parent_node.get_parent_node(); // Causing error


        if(ptr_parent == nullptr){
            break;
        };
    };

    reverse(path.begin(), path.end());
    return path;
}