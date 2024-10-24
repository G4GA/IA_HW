#include <graph.hpp>
#include <iostream>

Graph::Graph()
{
    std::cout << "Hi graph\n";
}

Node::Node(const std::string& name) : name(name)
{}

std::string Node::getName() const 
{
    return name;
}

