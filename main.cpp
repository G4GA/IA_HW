#include<GUI.hpp>
#include<graph.hpp>

const std::size_t HEIGHT = 800;
const std::size_t WIDTH = 1200;

int main (int argc, char *argv [])
{
    Graph myGraph;
    const std::string GRAPH_PATH = "./static/graph.txt";

    myGraph.loadFromFile(GRAPH_PATH);
/*
    for (const Connection* conn: myGraph.getAllConnections()) {
        std::cout << conn -> getFirst() -> getName() << std::endl
                  << conn -> getSecond() -> getName() << std::endl
                  << conn -> getWeight() << std::endl << std::endl;
    }

    std::cout << "-----------------------------------\n";

    for (const Node* nod: myGraph.getAllNodes()) {
        std::cout << nod -> getName() << std::endl;
    }*/

    MainWindow window(WIDTH, HEIGHT,
                      "Dijkstra's algorithm", myGraph);
    
    int result = window.run();

    return result;
}
