#include <GUI.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_map>
//Constant definitions

static const sf::Vector2f offsetPos(16.5f, 9.5f);

//Method definitions for GUI class
MainWindow::MainWindow(const size_t& width, const size_t& height,
                       const std::string& title, Graph& graph) :
    height(height), width(width), g_ui(graph, sf::Vector2f(width, height))
{
    settings.antialiasingLevel = 16;
    window.create(sf::VideoMode(width, height), 
                  title, sf::Style::Titlebar | sf::Style::Close, settings); 

    this -> graph = &graph;
    g_ui.loadMap(graphPath);
    graph.dijkstra(graph.getByName("A"));
}

int MainWindow::run() 
{
    return this -> eventLoop();
}

int MainWindow::eventLoop() 
{
    int result = 0;

    const Node* curNode = graph->getByName("J");
    std::vector<const Node*> shortestPath;
    shortestPath.push_back(curNode);
    while(curNode != nullptr) {
        for (auto predecesorPair : graph->getPredecesorMap()) {
            if (predecesorPair.first == curNode) {
                curNode = predecesorPair.second;
                if (curNode != nullptr) {
                    shortestPath.push_back(curNode);
                    
                }
            }
        }
    } 

    for (const Node* node : shortestPath) {
            g_ui.getByName(node->getName()).setColor(sf::Color::Green);
        }

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        drawGraph();

        window.display();
    }

    return result;
}

void MainWindow::drawGraph(){
    std::vector<const Connection*> connections = graph->getAllConnections();
    for (auto conn : connections) {
        ConnectionShape curLine = g_ui.getConnectionShape(conn);
        window.draw(curLine.getLine());
        window.draw(curLine.getText());
    }

    for (size_t i = 0; i < graph->getAllNodes().size(); i++) {
            NodeShape curShape = g_ui.getNodeShape(i);
            window.draw(curShape.getShape());
            window.draw(curShape.getLabel());
        }
}
//Method definitions for Node class
//Constructors
NodeShape::NodeShape
(const sf::Vector2i& gridPosition, const sf::Vector2f& cellSize,
 const Node* node, const sf::Font &font) :
    position(gridPosition)
{
    
    this -> node = node;
    realPos.x = position.x * cellSize.x;
    realPos.y = position.y * cellSize.y;
    buildShape();
    buildLabel(font);
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

const sf::Vector2f NodeShape::getRealPos() const
{
    return realPos;
}

//Private methods
void NodeShape::buildShape()
{
    shape.setRadius(SIZE);
    shape.setFillColor(sf::Color(LIGHT_BLUE));
    shape.setOutlineColor(sf::Color(BLUE));
    shape.setOutlineThickness(DEF_THICKNESS);
    shape.setPosition(sf::Vector2(realPos.x - SIZE, realPos.y - SIZE));
}

void NodeShape::buildLabel(const sf::Font &font)
{
    //A lot of magic numbers... It is what it is tho
    //TODO: Define constants for the magic numbers
    sf::Vector2f offset_position(7.f, 15.f);


    shapeLabel.setFont(font);
    shapeLabel.setString(node -> getName());
    shapeLabel.setCharacterSize(24);
    shapeLabel.setFillColor(sf::Color::Black);
    shapeLabel.setPosition(realPos.x - (offset_position.x),
                           realPos.y - (offset_position.y));
}

void NodeShape::setColor(const sf::Color& new_color) {
    shape.setFillColor(new_color);
}

//GraphUI Method

GraphUI::GraphUI
(Graph &graph, const sf::Vector2f& windowSize) :
    windowSize(windowSize)
{
    this -> graph = &graph;
    this -> font.loadFromFile(FONT_FP);
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
    const NodeShape *rNode = nullptr;
    for (std::vector<NodeShape>::const_iterator it = nodeShapes.begin(); it != nodeShapes.end(); it++) {
        if (counter == index) {
            rNode = &*it;
            break;
        } 
        counter ++;
    }
    return *rNode;
}

NodeShape &GraphUI::getByName
(const std::string &name)
{
    NodeShape *rNode = nullptr;
    for (std::vector<NodeShape>::iterator it = nodeShapes.begin(); it != nodeShapes.end(); it++) {
        if (it->getNodeName() == name) {
            rNode = &*it;
            break;
        }
    }
    return *rNode;
}

const std::string NodeShape::getNodeName() const {
    return node -> getName();
}

const ConnectionShape &GraphUI::getConnectionShape
(const Connection* conn) const 
{
    const ConnectionShape *rConn = nullptr;
    for (std::vector<ConnectionShape>::const_iterator it = connShapes.begin();
         it != connShapes.end(); it++) {

        if (it->getConnection() == conn) {
            rConn = &*it;
            break;
        }
    } 
    return *rConn;
}

void GraphUI::loadMap
(const std::string& filePath)
{
    std::ifstream fd(filePath);
    std::string line;

    if (fd.is_open()) {
        while (getline(fd, line, '=')) {
            if (line.compare(0, line.size(), "gridScale") == 0) {
                getline(fd, line);
                readVector(line, gridScale);
                gridScale.x = gridScale.x + 1;
                gridScale.y = gridScale.y + 1;
                setCellSize();
            } else {
                const Node *curNode = graph -> getByName(line);
                if (curNode) {
                    getline(fd, line);
                    sf::Vector2i position;
                    readVector(line, position);
                    NodeShape newNodeShape(position, cellSize, curNode, font);
                    nodeShapes.push_back(newNodeShape);
                }
            }
        }
    }
    buildConnShapes();
}

void GraphUI::setCellSize()
{
    if (!(this -> gridScale == sf::Vector2i(0, 0))) {
        cellSize.x = windowSize.x / gridScale.x;
        cellSize.y = windowSize.y / gridScale.y;
    }
}


void GraphUI::readVector
(std::string& line, sf::Vector2i& curVector)
{
    std::stringstream ss(line);
    std::string buffer;
    int vArray[2];

    for (int i = 0; getline(ss, buffer, ','); i++) {
        vArray[i] = std::stoi(buffer);
    }
    curVector.x = vArray[0]; 
    curVector.y = vArray[1]; 
}

void GraphUI::buildConnShapes()
{
    std::cout << "All connections, from GUI\n";
    for (const Connection* conn : graph->getAllConnections()) {
        /*std::cout << "Nodes: \n" << 
        "\tFirst: " << conn->getFirst()->getName() << "\n" <<
        "\tSecond: " << conn->getSecond()->getName() << "\n" <<
        "Weight: " << conn->getWeight() << "\n";*/
        NodeShape first = getByName(conn->getFirst()->getName());
        NodeShape second = getByName(conn->getSecond()->getName());

        ConnectionShape newLine(conn, first.getRealPos(),
                                second.getRealPos(), font);
        connShapes.push_back(newLine);
    }
}

//Method definitions for ConnectionShape class
ConnectionShape::ConnectionShape
(const Connection* connection, const sf::Vector2f &firstPos,
 const sf::Vector2f &secondPos, const sf::Font &font) :
    line(sf::Lines, VERTEX_SIZE)
{
    this -> connection = connection;
    initPoint(firstPos, 0);
    initPoint(secondPos, 1);
    initText(font);
}

const sf::VertexArray &ConnectionShape::getLine() const
{
    return line;
}

const Connection *ConnectionShape::getConnection() const
{
    return connection;
}

const sf::Text &ConnectionShape::getText() const
{
    return lineText;
}

void ConnectionShape::initPoint
(const sf::Vector2f& position, size_t index)
{
    line[index].position = sf::Vector2f(position);
    line[index].color = sf::Color(COLOR);
}

void ConnectionShape::initText
(const sf::Font &font)
{
    lineText.setFont(font);
    lineText.setString(std::to_string(connection->getWeight()));
    lineText.setFillColor(sf::Color::Black);
    lineText.setCharacterSize(20.f);

    float posX = (line[0].position.x + line[1].position.x) / 2;
    float posY = (line[0].position.y + line[1].position.y) / 2;

    sf::Vector2f textPosition(sf::Vector2f(posX, posY));
    lineText.setPosition(textPosition);
}

