#include<GUI.hpp>
#include<graph.hpp>
#include<iostream>

int main (int argc, char *argv [])
{
    Graph myGraph;

    MainWindow window(800, 600,
                      "Dijkstra's algorithm", myGraph);
    
    int result = window.run();

    return result;

    return 0;
}
