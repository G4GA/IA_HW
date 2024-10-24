#include <graph.hpp>
#include <iostream>
#include <fstream>


//Graph method definitions
Graph::Graph()
{}

int Graph::loadFromFile(const std::string& filepath)
{
    int rc = 0;
    int bSize;
    std::string line;
    char *c;
    std::ifstream fd(filepath);
    if (fd.is_open()) {
        getline(fd, line, '#');
        std::stoi(line, bSize);
    } else {
        rc = 1;
    }
    return rc;
}
//Node method definitions
Node::Node(const std::string& name) : name(name)
{}

std::string Node::getName() const 
{
    return name;
}

