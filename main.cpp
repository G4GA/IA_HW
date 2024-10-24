#include<GUI.hpp>
#include<graph.hpp>
#include<iostream>

int main (int argc, char *argv [])
{
    /*sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    MainWindow window(600, 800,
                      "Dijkstra's algorithm", settings);
    
    int result = window.run();

    return result;*/

    std::string filepath(argv[1]);
    int rc;
    Graph testing;
    rc = testing.loadFromFile(filepath);

    if (rc) {
        std::cout << "Could not open file";
    }

    return 0;
}
