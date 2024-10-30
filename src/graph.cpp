#include <graph.hpp>
#include <iostream>
#include <fstream>


//Graph method definitions
Graph::Graph()
{}

int Graph::loadFromFile(const std::string& filepath)
{
    int rc = 0;
    size_t bSize;
    std::string line;
    char *c;
    std::ifstream fd(filepath);
    if (fd.is_open()) {
        getline(fd, line, '#');
        std::stoi(line, &bSize);
    } else {
        rc = 1;
    }
    return rc;
}

Node   Graph::getByName
(const std::string&)
{}

size_t Graph::getConnectionWeight()
{}

void Graph::createNode
(const Node& node)
{
    this -> nodes.push_back(Node(node));
}

void Graph::createNode
(const std::string& name)
{
    this -> nodes.push_back(Node(name));
}

void Graph::createConnection
(const Node& first, const Node& second, size_t weight)
{
    //Of course this is missing a least a few validations
    //sadly, there is no time for that now so
    //TODO: Somewhere in the future, add them validations
    this -> connections.push_back(Connection(first, second, weight));
}

std::vector<const Node*> Graph::getConnectedNodes
(const Node& node) const
{
    std::vector<const Node*> connectedNodes;
    for
    (auto conIt = connections.begin(); conIt != connections.end(); conIt ++) {
        const Node *first = conIt -> getFirst();
        const Node *second = conIt -> getSecond();
        if 
        (node.getName() == first -> getName()) {
            const Node *myNode 
            connectedNodes.push_back(const Node(second));
        }

    }

    return connectedNodes;
}

std::vector<const Node*> Graph::dijkstra
(const Node&) const
{}

std::vector<const Node*> Graph::getNodes() const
{}

int loadFromFile
(const std::string&)
{}

//Node method definitions
Node::Node
(const std::string& name) : 
    name(name)
{}

Node::Node
(const Node& node) :
    name(node.getName())
{}

std::string Node::getName() const 
{
    return name;
}


//Connection method definitions
Connection::Connection
(const Node& first, const Node& second, size_t weight) :
    weight(weight)
{
    this -> first = &first;
    this -> second = &second;
}

const Node *Connection::getFirst() const
{
    return this -> first;
}

const Node *Connection::getSecond() const
{
    return this -> second;
}

size_t Connection::getWeight() const
{
    return weight;
}
