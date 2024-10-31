#include <GUI.hpp>
//Constant definitions

static const sf::Vector2f offsetPos(16.5f, 9.5f);

//Method definitions for GUI class
MainWindow::MainWindow(const size_t& width, const size_t& height,
                       const std::string& title, Graph& graph) :
    height(height), width(width)
{
    settings.antialiasingLevel = 16;
    window.create(sf::VideoMode(width, height), 
                  title, sf::Style::Titlebar | sf::Style::Close, settings); 

    this -> graph = &graph;
}

int MainWindow::run() 
{
    return this -> eventLoop();
}

int MainWindow::eventLoop() 
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

//Method definitions for Node class
//Constructors
NodeShape::NodeShape
(const sf::Vector2i& gridPosition, const sf::Vector2f& cellSize, const Node* node) :
    position(gridPosition)
{
    this -> node = node;
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
}
