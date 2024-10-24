#include <GUI.hpp>
#include <iostream>
//Constant definitions

//Method definitions for GUI class
MainWindow::MainWindow(const size_t& width, const size_t& height,
                       const std::string& title, const sf::ContextSettings& settings) : 
    window(sf::VideoMode(height, width), 
           title, sf::Style::Titlebar | sf::Style::Close, settings),
    height(),
    width()
{}

int MainWindow::run() {
    return this -> eventLoop();
}

int MainWindow::eventLoop() 
{
    int result = 0;
    Node node("A");
    Node node2("B");
    NodeShape node_sh(sf::Vector2f(250, 250), node);
    NodeShape node_sh2(sf::Vector2f(150, 250), node2);
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        
        window.draw(node_sh.getShape());
        window.draw(node_sh2.getShape());
        window.draw(node_sh2.getLabel());
        window.draw(node_sh.getLabel());
        window.display();
    }

    return result;
}

//Method definitions for Node class
//Constructors
NodeShape::NodeShape(const sf::Vector2f& position, const Node& node) :
    node(node),
    shape(SIZE),
    position(position)
{
    buildShape();
    buildLabel();
}

//Getters
const sf::CircleShape& NodeShape::getShape() const 
{
    return shape;
}

const sf::Text& NodeShape::getLabel() const
{
    return shapeLabel;
}

//Private methods
void NodeShape::buildShape()
{
    shape.setPosition(position);
    shape.setFillColor(sf::Color(LIGHT_BLUE));
    shape.setOutlineColor(sf::Color(BLUE));
    shape.setOutlineThickness(DEF_THICKNESS);
}

void NodeShape::buildLabel()
{
    //A lot of magic numbers... It is what it is tho
    //TODO: Define constants for the magic numbers
    sf::Vector2f offset_position(16.5f, 9.5f);
    font.loadFromFile(FONT_FP);

    shapeLabel.setFont(font);
    shapeLabel.setString(node.getName());
    shapeLabel.setCharacterSize(24);
    shapeLabel.setFillColor(sf::Color::Black);
    shapeLabel.setPosition(position + offset_position);
}
