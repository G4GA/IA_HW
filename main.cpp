#include<GUI.hpp>
#include<graph.hpp>

int main ()
{
    GUI gui(500, 500);
    Graph graph;
    
    int result = gui.run();

    return result;
}
