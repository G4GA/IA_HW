#pragma once

#include<iostream>
#include<string>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

class GUI {
    public:
        GUI(const size_t&, const size_t&);

        int run();

    private:
        //Private attributtes
        sf::RenderWindow window;
        size_t height;
        size_t width;

};
