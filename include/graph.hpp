#pragma once

#include <vector>
#include <string>
#include <unordered_map>

class Node {
    public:
        Node(const std::string&); //Done
        Node(const Node&); //Done
        //Getters
        std::string getName() const; //Done
    private:
        std::string name;
};

class Connection {
    public:
        Connection(const Node*, const Node*, size_t); //Done
        //Getters
        const Node *getFirst() const; //Done
        const Node *getSecond() const; //Done
        size_t getWeight() const; //Done
    private:
        const Node *first;
        const Node *second;
        size_t weight;
};

class Graph {
    public:
        Graph();
        ~Graph();
        const Node* getByName(const std::string&);
        const Connection* getConnection(const Node*, const Node*) const;

        void createNode(const Node&);
        void createNode(const std::string&);
        void createConnection(const Node*, const Node*, size_t);

        std::vector<const Node*> getConnectedNodes(const Node*) const;
        std::vector<const Connection*> getConnections(const Node*) const;
        void dijkstra(const Node*);

        int loadFromFile (const std::string&);

        std::vector<const Node*> getAllNodes() const;
        std::vector<const Connection*> getAllConnections() const;
        std::unordered_map<const Node*, const Node*> getPredecesorMap() const;
        std::unordered_map<const Node*, size_t> getShortestDistance() const;

    private:
        std::vector<const Node*> nodes;
        std::vector<const Connection*> connections;
        std::unordered_map<const Node*, const Node*> predecesorMap;
        std::unordered_map<const Node*, size_t> distances;
        void getSecondNode(std::string&, std::string&, size_t&);

};

