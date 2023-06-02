/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

    #include <SFML/Graphics.hpp>
    #include "Parse.hpp"

    #define C_PX 2  // resolution
    #define C_P 3   // position
    #define C_R 4   // rotation
    #define C_FOV 5 // FOV
    #define ADD_P 6 // ADD Primitive
    #define ADD_L 7 // ADD Light


    class Window {
        public:
            Window (char **argv);
            ~Window(){};
            void display();
            void init_div();
            void display_rectangles();
            void display_text();
            void display_img (sf::Sprite sprite);
            void execute();
            void debug();
            void event();
            bool is_int_div(std::vector<sf::RectangleShape> vecteur, int i);
        private:
            sf::RenderWindow *_window;
            sf::Font font;
            std::vector<sf::Text> div_settings_text;
            std::vector<sf::RectangleShape> div_settings;
            std::vector<sf::RectangleShape> primitive;
            std::vector<sf::RectangleShape> light;
            std::vector<sf::RectangleShape> div_display;
            Parse *CFG;
            std::string path_makefile;
            std::string path_cfg;
            std::string path_ppm;
            bool file_exist;
            sf::Texture texture_ppm;
            std::string make = "make re";
            int scroll = 0;
            sf::View view;
    };

#endif /* !WINDOW_HPP_ */

