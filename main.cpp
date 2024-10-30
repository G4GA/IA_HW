#include<GUI.hpp>
#include<graph.hpp>
#include<iostream>

int main (int argc, char *argv [])
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    Graph myGraph;

    MainWindow window(800, 600,
                      "Dijkstra's algorithm", settings,
                      myGraph);
    
    int result = window.run();

    return result;

    return 0;
}
