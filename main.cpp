#include<GUI.hpp>
#include<graph.hpp>

int main ()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    MainWindow window(600, 800,
                      "Dijkstra's algorithm", settings);
    
    int result = window.run();

    return result;
}
