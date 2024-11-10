#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <graph.hpp>

class NodeShape {
    public:
        NodeShape(const sf::Vector2i&, const sf::Vector2f&,
                  const Node*, const sf::Font&);
    //Getters and setter
        const sf::CircleShape& getShape() const; //Done
        const sf::Text& getLabel() const;//Done
        const sf::Vector2i getPos() const;
        const sf::Vector2f getRealPos() const;
        const std::string getNodeName() const;
        void setColor(const sf::Color&);
        void setRealPos(sf::Vector2f);
    //Public const expressions
        static constexpr float SIZE = 24.f;
        static constexpr sf::Uint32 LIGHT_BLUE = 0xC4E1F6;
        static constexpr sf::Uint32 BLUE = 0x0D92F4;
    private:
        //Attributes
        sf::CircleShape shape;
        sf::Text shapeLabel;
        static const sf::Vector2f offsetPos;

        sf::Vector2i position;
        sf::Vector2f realPos;
        const Node* node;
        //Constants
        
        static constexpr float DEF_THICKNESS = 2.f;
        //Methods
        void buildShape();//Done
        void buildLabel(const sf::Font&);//Done
};

class ConnectionShape {
    public:
        ConnectionShape(const Connection*,
                        const sf::Vector2f&,
                        const sf::Vector2f&,
                        const sf::Font&);
        const Connection *getConnection() const;
        sf::VertexArray &getLine();
        sf::Text &getText();
        static constexpr sf::Uint32 COLOR = 0xC62E2EFF;
    private:
        //Attributes
        const Connection* connection;
        sf::VertexArray line;
        sf::Text lineText;
        static constexpr size_t VERTEX_SIZE = 2;
        void initPoint(const sf::Vector2f&,
                       size_t);
        void initText(const sf::Font&);

};

class GraphUI {
    public:
        GraphUI(Graph&, const sf::Vector2f&);
        //getters
        sf::Vector2f getCellSize() const; //Done
        float getCellXSize() const; //Done
        float getCellYSize() const; //Done
        sf::Vector2i getGridScale() const; //Done

        NodeShape &getNodeShape(size_t);
        NodeShape &getByName(const std::string&);
        ConnectionShape &getConnectionShape(const Connection*);
        //Methods
        void loadMap(const std::string&);
        void colorPath(const Node*);
        void resetColors();
    private:
        //attributes
        sf::Vector2f cellSize;
        sf::Vector2i gridScale;
        sf::Vector2f windowSize;
        Graph        *graph;
        sf::Font font;

        const std::string FONT_FP = "./static/JetBrainsMono-Regular.ttf";

        std::vector<NodeShape> nodeShapes;
        std::vector<ConnectionShape> connShapes;
        //Methods
        void readVector(std::string&, sf::Vector2i&);
        void buildConnShapes();
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
        void drawGraph();
        //Constant attributes
        const std::string graphPath = "./static/placement.txt";
};

