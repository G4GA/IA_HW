#include <GUI.hpp>

GUI::GUI(const size_t& width, const size_t& height) : 
    window(sf::VideoMode(height, width), "Dijkstra's algorithm", sf::Style::Titlebar | sf::Style::Close),
    height(),
    width()
{}

int GUI::run() 
{
    int result = 0;
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        window.display();
    }

    return result;
}
