#pragma once

#include <vector>
#include <string>

class Node {
    public:
        Node(const std::string&);
        //Getters
        std::string getName() const;
    private:
        std::string name;
};

class Connection {
    public:
        Connection(const Node&, const Node&, size_t weight);
        //Getters
        const Node& getFirst() const;
        const Node& getSecond() const;
        size_t getWeight() const;
    private:
        Node& first;
        Node& second;
        size_t weight;
};

class Graph {
    public:
        Graph();
    private:
        std::vector<Node> nodes;
        std::vector<Connection> connections;

};

