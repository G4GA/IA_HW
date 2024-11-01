#pragma once

#include <vector>
#include <string>

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
        const Node* getByName(const std::string&);
        size_t getConnectionWeight(const Connection*);
        bool areConnected(const Node*, const Node*);
        const Connection* getConnection(const Node*, const Node*);

        void createNode(const Node&);
        void createNode(const std::string&);
        void createConnection(const Node*, const Node*, size_t);

        std::vector<const Node*> getConnectedNodes(const Node*) const;
        std::vector<const Node*> dijkstra(const Node*) const;
        std::vector<const Node*> getNodes() const;

        int loadFromFile (const std::string&);

        std::vector<const Node*> getAllNodes() const;
        std::vector<const Connection*> getAllConnections() const;
    private:
        std::vector<const Node*> nodes;
        std::vector<const Connection*> connections;
        void getSecondNode(std::string&, std::string&, size_t&);

};

