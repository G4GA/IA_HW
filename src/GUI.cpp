#include <GUI.hpp>
#include <fstream>
#include <sstream>
#include <string>
//Constant definitions

static const sf::Vector2f offsetPos(16.5f, 9.5f);

//Method definitions for GUI class
MainWindow::MainWindow(const size_t& width, const size_t& height,
                       const std::string& title, Graph& graph) :
    height(height), width(width), g_ui(graph)
{
    settings.antialiasingLevel = 16;
    window.create(sf::VideoMode(width, height), 
                  title, sf::Style::Titlebar | sf::Style::Close, settings); 

    this -> graph = &graph;
    g_ui.loadMap(graphPath);
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
    shapeLabel.setString(node -> getName());
    shapeLabel.setCharacterSize(24);
    shapeLabel.setFillColor(sf::Color::Black);
}

//GraphUI Method

GraphUI::GraphUI
(Graph &graph, const sf::Vector2f& gridScale) :
    gridScale(gridScale) 
{
    this -> graph = &graph;
}

GraphUI::GraphUI
(Graph& graph)
{
    this -> graph = &graph;
}

sf::Vector2f GraphUI::getCellSize () const
{
    return cellSize;
}

sf::Vector2i GraphUI::getGridScale () const
{
    return gridScale;
}

float GraphUI::getCellXSize () const
{
    return cellSize.x;
}

float GraphUI::getCellYSize () const
{
    return cellSize.y;
}

const NodeShape &GraphUI::getNodeShape
(size_t index) const
{
    size_t counter = 0;
    const NodeShape *rNode;
    for (std::vector<NodeShape>::const_iterator it = nodeShapes.begin(); it != nodeShapes.end(); it++) {
        if (counter == index) {
            rNode = &*it;
        } 
    }
    return *rNode;
}

void GraphUI::loadMap
(const std::string& filePath)
{
    std::ifstream fd(filePath);
    std::string line;

    if (fd.is_open()) {
        std::cout << "GraphUI::LoadMap\n";
        while (getline(fd, line, '=')) {
            if (line.compare(0, line.size(), "gridScale") == 0) {
                getline(fd, line);
                readVector(line, gridScale);
            } else {
                graph -> getByName(line);
                if (graph) {
                    getline(fd, line);

                }
            }
        }
    }

}

void GraphUI::setCellSize() {

}


void GraphUI::readVector
(std::string& line, sf::Vector2i& curVector)
{
    std::stringstream ss(line);
    std::string buffer;
    int vArray[2];
    std::cout << line << "\n";

    for (int i = 0; getline(ss, buffer, ','); i++) {
        vArray[i] = std::stoi(buffer);
    }
    curVector.x = vArray[0]; 
    curVector.y = vArray[1]; 
}

