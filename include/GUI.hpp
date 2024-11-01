#pragma once

#include<iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <graph.hpp>

class NodeShape {
    public:
        NodeShape(const sf::Vector2i&, const sf::Vector2f&, const Node*);
    //Getters and setter
        const sf::CircleShape& getShape() const; //Done
        const sf::Text& getLabel() const;//Done
        const sf::Vector2i getPos() const;
        const sf::Vector2f getRealPos() const;
        const std::string getNodeName() const;
        void setRealPos(sf::Vector2f);
    //Public const expressions
        static constexpr float SIZE = 24.f;
    private:
        //Attributes
        sf::CircleShape shape;
        sf::Font font;
        sf::Text shapeLabel;
        static const sf::Vector2f offsetPos;

        sf::Vector2i position;
        sf::Vector2i realPos;
        const Node* node;
        //Constants
        static constexpr sf::Uint32 LIGHT_BLUE = 0xC4E1F6;
        static constexpr sf::Uint32 BLUE = 0x0D92F4;
        static constexpr float DEF_THICKNESS = 2.f;
        const std::string FONT_FP = "./static/JetBrainsMono-Regular.ttf";
        //Methods
        void buildShape();//Done
        void buildLabel();//Done
};

class GraphUI {
    public:
        GraphUI(Graph&, const sf::Vector2f&);
        GraphUI(Graph&);
        //getters
        sf::Vector2f getCellSize() const; //Done
        float getCellXSize() const; //Done
        float getCellYSize() const; //Done
        sf::Vector2i getGridScale() const; //Done

        const NodeShape &getNodeShape(size_t) const;
        //Methods
        void loadMap(const std::string&);
    private:
        //attributes
        sf::Vector2f cellSize;
        sf::Vector2i gridScale;
        Graph        *graph;

        std::vector<NodeShape> nodeShapes;
        sf::VertexArray        connnectionLines;
        //Methods
        void readVector(std::string&, sf::Vector2i&);
        void addNodeShape(const Node&);
        void setCellSize(); 
};

class MainWindow {
    public:
        MainWindow(const size_t&, const size_t&,
                   const std::string&,Graph&);
        int run();
    private:
        //Private attributtes
        sf::RenderWindow window;
        sf::ContextSettings settings;
        Graph *graph;
        GraphUI g_ui;
        float height;
        float width;
        //Constants
        //Private methods
        int eventLoop();
        //Constant attributes
        const std::string graphPath = "./static/placement.txt";
};

