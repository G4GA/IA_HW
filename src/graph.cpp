#include <graph.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


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

        while(getline(fd, line)) {
            std::string nodeKey = "#Nodes"; 
            std::string connectionKey = "#Connections";

            if (line.compare(0, nodeKey.size(), nodeKey) == 0) {
                getline(fd, line);
                std::stringstream ss(line);
                std::string nodeName;
                while (std::getline(ss, nodeName, ',')) {
                    createNode(nodeName);
                }

            } else if (line.compare(0, connectionKey.size(), connectionKey) == 0) {
                while(getline(fd, line)) {
                    std::stringstream ss(line);
                    const Node *firstNode;
                    std::string nodeName;

                    getline(ss, nodeName, ':');
                    firstNode = getByName(nodeName);

                    if (firstNode) {
                        while(getline(ss, line, ';')) {
                            size_t weight;
                            std::string secNodename;
                            const Node *secondNode;
                            getSecondNode(line, secNodename, weight);
                            secondNode = getByName(secNodename);
                            if (!secondNode) {
                                createNode(secNodename);
                            }
                            createConnection(firstNode, secondNode, weight);
                        }
                    }
                }
            } else {
                rc = 2;
            }
        }
    } else {
        rc = 1;
    }
    return rc;
}

void Graph::getSecondNode
(std::string& line, std::string& nodeName, size_t& weight)
{
    std::stringstream ss(line);
    std::string weightStr;
    getline(ss, weightStr, ',');
    getline(ss, nodeName);

    weight = std::stol(weightStr);
}

const Node* Graph::getByName
(const std::string& name)
{
    const Node *match = nullptr;

    for (const Node *curNode: nodes) {
        if (curNode -> getName() == name) {
            match = curNode;
        }
    }

    return match;
}

size_t Graph::getConnectionWeight(const Connection* conn)
{

}

const Connection *Graph::getConnection
(const Node* first, const Node*second) const
{
    
}

void Graph::createNode
(const Node& node)
{
    const Node *newNode = new Node(node);
    this -> nodes.push_back(newNode);
}

void Graph::createNode
(const std::string& name)
{
    const Node *newNode = new Node(name); 
    this -> nodes.push_back(newNode);
}

void Graph::createConnection
(const Node* first, const Node* second, size_t weight)
{
    //Of course this is missing a least a few validations
    //sadly, there is no time for that now so
    //TODO: Somewhere in the future, add them validations
    const Connection *newConnection = new Connection(first, second, weight);
    this -> connections.push_back(newConnection);
}

std::vector<const Node*> Graph::getConnectedNodes
(const Node* node) const
{
    std::vector<const Node*> connectedNodes;
    for
    (const Connection *conIt = *connections.begin(); conIt != *connections.end(); conIt ++) {
        const Node *first = conIt -> getFirst();
        const Node *second = conIt -> getSecond();

        if (node -> getName() == first -> getName()) {
            connectedNodes.push_back(second);
        } else if (node -> getName() == second -> getName()) {
            connectedNodes.push_back(first);
        }

    }

    return connectedNodes;
}

std::vector<const Node*> Graph::dijkstra
(const Node*) const
{}

std::vector<const Node*> Graph::getNodes() const
{}

std::vector<const Node*> Graph::getAllNodes () const
{
    return nodes;
}
std::vector<const Connection*> Graph::getAllConnections () const 
{
    return connections;
}

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
(const Node* first, const Node* second, size_t weight) :
    weight(weight),
    first(first),
    second(second)
{}

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
