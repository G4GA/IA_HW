#pragma once

#include<iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <graph.hpp>

class NodeShape {
    public:
        NodeShape(const sf::Vector2f&, const Node&);
    //Getters and setter
        const sf::CircleShape& getShape() const;
        const sf::Text& getLabel() const;
    //Public const expressions
        static constexpr float SIZE = 24.f;
    private:
        //Attributes
        sf::CircleShape shape;
        sf::Font font;
        sf::Text shapeLabel;
        sf::Vector2f position;
        const Node& node;
        //Constants
        static constexpr sf::Uint32 LIGHT_BLUE = 0xC4E1F6;
        static constexpr sf::Uint32 BLUE = 0x0D92F4;
        static constexpr float DEF_THICKNESS = 2.f;
        const std::string FONT_FP = "./static/JetBrainsMono-Regular.ttf";
        //Methods
        void buildShape();
        void buildLabel();
};

class GraphUI {
    public:
        GraphUI(Graph&, const size_t&, const sf::Vector2f&);
        //getters
        sf::Vector2f getCellSize() const;
        float getCellXSize() const;
        float getCellYSize() const;
        size_t getGridScale() const;
    private:
        sf::Vector2f cellSize;
        size_t gridScale;
        Graph *graph;
        std::vector<NodeShape> nodeShapes;

};
class MainWindow {
    public:
        MainWindow(const size_t&, const size_t&,
                   const std::string&, const Graph&);
        int run();
    private:
        //Private attributtes
        sf::RenderWindow window;
        sf::ContextSettings settings;
        const Graph *graph;
        float height;
        float width;
        //Private methods
        int eventLoop();
};

