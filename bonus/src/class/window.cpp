/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** window
*/

#include "my.hpp"
#include "color.hpp"
#include <cstdlib>
#include <filesystem>
#include <SFML/Graphics.hpp>

void Window::debug()
{
    if (CFG) {
        std::cout << "CFG" << std::endl;
        std::cout << "----- Camera" << std::endl;
        std::cout << "Camera fov " << CFG->get_camera().fov << std::endl;
        std::cout << "Camera height " << CFG->get_camera().height << std::endl;
        std::cout << "Camera width " << CFG->get_camera().width << std::endl;
        std::cout << "Camera posX " << CFG->get_camera().posX << std::endl;
        std::cout << "Camera posY " << CFG->get_camera().posY << std::endl;
        std::cout << "Camera posZ " << CFG->get_camera().posZ << std::endl;
        std::cout << "Camera rotX " << CFG->get_camera().rotX << std::endl;
        std::cout << "Camera rotY " << CFG->get_camera().rotY << std::endl;
        std::cout << "Camera posZ " << CFG->get_camera().posZ << std::endl;
        std::cout << std::endl;

        std::cout << "----- Lights" << std::endl;
        int count = 0;
        for (auto i : CFG->get_light()) {
            std::cout << "Light " << count << " ambient : " << i.ambient << std::endl;
            std::cout << "Light " << count << " diffuse : " << i.diffuse << std::endl;
            std::cout << "Light " << count << " posX : " << i.posX << std::endl;
            std::cout << "Light " << count << " posY : " << i.posY << std::endl;
            std::cout << "Light " << count << " posZ : " << i.posZ << std::endl;
            std::cout << "Light " << count << " type : " << i.type << std::endl;
            std::cout << std::endl;
            count++;
        }

        std::cout << "----- Primitives" << std::endl;
        count = 0;
        for (auto i : CFG->get_primitive()) {
            std::cout << "Primitive " << count << " axis : " << i.axis << std::endl;
            std::cout << "Primitive " << count << " Color : " << i.ColorR << " " << i.ColorG << " " << i.ColorB << std::endl;
            std::cout << "Primitive " << count << " position : " << i.position << std::endl;
            std::cout << "Primitive " << count << " radius : " << i.radius << std::endl;
            std::cout << "Primitive " << count << " pos : "<< i.posX << " " << i.posY << " " << i.posZ << std::endl;
            std::cout << "Primitive " << count << " type : " << i.type << std::endl;
            std::cout << std::endl;
            count++;
        }
        exit(0);
    }
}

Window::Window (char **argv)
{
    this->path_makefile = argv[1];
    this->path_cfg = argv[2];
    this->path_ppm = argv[3];

    sf::VideoMode _mode = sf::VideoMode::getDesktopMode();
    this->_window = new sf::RenderWindow(_mode, "Bonus", sf::Style::Resize | sf::Style::Close);
    font.loadFromFile("./asset/Hertical_Sans.ttf");
    std::ifstream file(this->path_cfg);
    if (file) {
        file_exist = true;
        CFG = new Parse(this->path_cfg);
    } else {
        std::ofstream file(this->path_cfg);
        if (file) {
            file_exist = true;
            CFG = new Parse(this->path_cfg);
        }
        else {
            std::cerr << "Erreur lors de la création du fichier." << std::endl;
            file_exist = false;
        }
    }
    execute();
}

void Window::init_div ()
{
    sf::VideoMode _mode = sf::VideoMode::getDesktopMode();

    sf::RectangleShape div_settings_page(sf::Vector2f(((_mode.width/100) * 20), _mode.height));
    div_settings_page.setFillColor(sf::Color::Black);
    this->div_settings.push_back(div_settings_page);

    sf::RectangleShape div_settings_camera(sf::Vector2f(((div_settings_page.getSize().x/100) * 90), ((div_settings_page.getSize().y/100) * 20)));
    div_settings_camera.setPosition(sf::Vector2f(((div_settings_page.getSize().x/100) * 5), ((div_settings_page.getSize().x/100) * 5)));
    div_settings_camera.setFillColor(sf::Color::White);
    this->div_settings.push_back(div_settings_camera);

    sf::Text text_camera_title("Camera", font, (_mode.width/100) * 1);
    text_camera_title.setPosition(sf::Vector2f(((div_settings_page.getSize().x/100) * 5), 0));
    this->div_settings_text.push_back(text_camera_title);

    sf::RectangleShape div_settings_camera_resolution(sf::Vector2f(((div_settings_camera.getSize().x/100) * 96), ((div_settings_camera.getSize().y/100) * 23.5)));
    div_settings_camera_resolution.setPosition(sf::Vector2f((div_settings_camera.getPosition().x + ((div_settings_camera.getSize().x/100) * 2)), (div_settings_camera.getPosition().y + ((div_settings_camera.getSize().y/100) * 1))));
    div_settings_camera_resolution.setFillColor(SFML_Grey_Light);
    this->div_settings.push_back(div_settings_camera_resolution);

    sf::Text text_camera_resolution("PX", font, (_mode.width/100) * 1.3);
    text_camera_resolution.setPosition(sf::Vector2f(div_settings.back().getPosition().x + 10, (div_settings.back().getPosition().y + (div_settings.back().getSize().y / 3.5)))); //
    this->div_settings_text.push_back(text_camera_resolution);

    sf::RectangleShape div_settings_camera_position(sf::Vector2f(((div_settings_camera.getSize().x/100) * 96), ((div_settings_camera.getSize().y/100) * 23.5)));
    div_settings_camera_position.setPosition(sf::Vector2f((div_settings_camera.getPosition().x + ((div_settings_camera.getSize().x/100) * 2)), (div_settings.back().getPosition().y + div_settings.back().getSize().y) + ((div_settings_camera.getSize().y/100) * 1)));
    div_settings_camera_position.setFillColor(SFML_Grey_Light);
    this->div_settings.push_back(div_settings_camera_position);

    sf::Text text_camera_position("P", font, (_mode.width/100) * 1.3);
    text_camera_position.setPosition(sf::Vector2f(div_settings.back().getPosition().x + 10, (div_settings.back().getPosition().y + (div_settings.back().getSize().y / 3.5)))); //
    this->div_settings_text.push_back(text_camera_position);

    sf::RectangleShape div_settings_camera_rotation(sf::Vector2f(((div_settings_camera.getSize().x/100) * 96), ((div_settings_camera.getSize().y/100) * 23.5)));
    div_settings_camera_rotation.setPosition(sf::Vector2f((div_settings_camera.getPosition().x + ((div_settings_camera.getSize().x/100) * 2)), (div_settings.back().getPosition().y + div_settings.back().getSize().y) + ((div_settings_camera.getSize().y/100) * 1)));
    div_settings_camera_rotation.setFillColor(SFML_Grey_Light);
    this->div_settings.push_back(div_settings_camera_rotation);

    sf::Text text_camera_rotation("R", font, (_mode.width/100) * 1.3);
    text_camera_rotation.setPosition(sf::Vector2f(div_settings.back().getPosition().x + 10, (div_settings.back().getPosition().y + (div_settings.back().getSize().y / 3.5)))); //
    this->div_settings_text.push_back(text_camera_rotation);

    sf::RectangleShape div_settings_camera_fov(sf::Vector2f(((div_settings_camera.getSize().x/100) * 96), ((div_settings_camera.getSize().y/100) * 23.5)));
    div_settings_camera_fov.setPosition(sf::Vector2f((div_settings_camera.getPosition().x + ((div_settings_camera.getSize().x/100) * 2)), (div_settings.back().getPosition().y + div_settings.back().getSize().y) + ((div_settings_camera.getSize().y/100) * 1)));
    div_settings_camera_fov.setFillColor(SFML_Grey_Light);
    this->div_settings.push_back(div_settings_camera_fov);

    sf::Text text_camera_FOV("FOV", font, (_mode.width/100) * 1.3);
    text_camera_FOV.setPosition(sf::Vector2f(div_settings.back().getPosition().x + 10, (div_settings.back().getPosition().y + (div_settings.back().getSize().y / 3.5))));
    this->div_settings_text.push_back(text_camera_FOV);

    sf::RectangleShape div_settings_primitive_add(sf::Vector2f(((div_settings_page.getSize().x/100) * 90), ((div_settings_page.getSize().y/100) * 5)));
    div_settings_primitive_add.setPosition(sf::Vector2f(((div_settings_page.getSize().x/100) * 5), ((div_settings_camera.getPosition().y + div_settings_camera.getSize().y) + (_mode.height/100) * 2.5)));
    div_settings_primitive_add.setFillColor(SFML_Grey_Light);
    this->div_settings.push_back(div_settings_primitive_add);

    sf::Text text_primitive_add("Add Primitive", font, (_mode.width/100) * 1.3);
    text_primitive_add.setPosition(sf::Vector2f(div_settings.back().getPosition().x + 10, (div_settings.back().getPosition().y + (div_settings.back().getSize().y / 3.5))));
    this->div_settings_text.push_back(text_primitive_add);

    // for (auto i : CFG->get_primitive()) {
    //     int tmp_pos_y_p = (div_settings.back().getPosition().y + div_settings.back().getSize().y);
    //     if (primitive.size())
    //         tmp_pos_y_p = (primitive.back().getPosition().y + primitive.back().getSize().y);
    //     sf::RectangleShape div_settings_primitive_box_tmp(sf::Vector2f(((div_settings_page.getSize().x/100) * 90), ((div_settings_page.getSize().y/100) * 20)));
    //     div_settings_primitive_box_tmp.setPosition(sf::Vector2f(((div_settings_page.getSize().x/100) * 5), (tmp_pos_y_p + (_mode.height/100) * 2.5)));
    //     div_settings_primitive_box_tmp.setFillColor(SFML_White);
    //     this->primitive.push_back(div_settings_primitive_box_tmp);
    // }

    int tmp_pos_y = (div_settings.back().getPosition().y + div_settings.back().getSize().y);
    if (primitive.size())
        tmp_pos_y = (primitive.back().getPosition().y + primitive.back().getSize().y);

    sf::RectangleShape div_settings_light_add(sf::Vector2f(((div_settings_page.getSize().x/100) * 90), ((div_settings_page.getSize().y/100) * 5)));
    div_settings_light_add.setPosition(sf::Vector2f(((div_settings_page.getSize().x/100) * 5), (tmp_pos_y + (_mode.height/100) * 2.5)));
    div_settings_light_add.setFillColor(SFML_Grey_Light);
    this->div_settings.push_back(div_settings_light_add);

    sf::Text text_light_add("Add Point", font, (_mode.width/100) * 1.3);
    text_light_add.setPosition(sf::Vector2f(div_settings.back().getPosition().x + 10, (div_settings.back().getPosition().y + (div_settings.back().getSize().y / 3.5))));
    this->div_settings_text.push_back(text_light_add);

    // for (auto i : CFG->get_light()) {
    //     int tmp_pos_y_p = (div_settings.back().getPosition().y + div_settings.back().getSize().y);
    //     if (light.size())
    //         tmp_pos_y_p = (light.back().getPosition().y + light.back().getSize().y);
    //     sf::RectangleShape div_settings_light_box_tmp(sf::Vector2f(((div_settings_page.getSize().x/100) * 90), ((div_settings_page.getSize().y/100) * 20)));
    //     div_settings_light_box_tmp.setPosition(sf::Vector2f(((div_settings_page.getSize().x/100) * 5), (tmp_pos_y_p + (_mode.height/100) * 2.5)));
    //     div_settings_light_box_tmp.setFillColor(SFML_White);
    //     this->light.push_back(div_settings_light_box_tmp);
    // }

    sf::RectangleShape div_settings_button_save(sf::Vector2f(((div_settings_page.getSize().x/100) * 90), ((div_settings_page.getSize().y/100) * 7)));
    div_settings_button_save.setPosition(sf::Vector2f(((div_settings_page.getSize().x/100) * 5), (((div_settings_page.getSize().y) / 100) * 85)));
    div_settings_button_save.setFillColor(SFML_Blue_twitter);
    this->div_settings.push_back(div_settings_button_save);

    sf::Text text_camera_save("Enregistrer", font, (_mode.width/100) * 2.5);
    text_camera_save.setPosition(sf::Vector2f(div_settings.back().getPosition().x + 10, (div_settings.back().getPosition().y + (div_settings.back().getSize().y / 5)))); //
    this->div_settings_text.push_back(text_camera_save);

    sf::RectangleShape div_displays(sf::Vector2f(((_mode.width/100) * 83), _mode.height));
    div_displays.setPosition(sf::Vector2f(((_mode.width/100) * 20.1), 0));
    div_displays.setFillColor(sf::Color::White);
    this->div_display.push_back(div_displays);

    if (!file_exist) {
        sf::Text text_display_error("example.cfg : File not found", font, (_mode.width/100) * 2.5);
        text_display_error.setPosition(sf::Vector2f((div_display.back().getPosition().x +(div_display.back().getSize().x/100) * 25), (div_display.back().getSize().y/100) * 40)); //
        text_display_error.setFillColor(SFML_Grey_Light);
        this->div_settings_text.push_back(text_display_error);
    }
}

void Window::display_rectangles()
{
    // int j = 0;

    for (auto i : div_display) {
        _window->draw(i);
    }
    for (auto i : div_settings) {
        // if (j)
            // i.setPosition(sf::Vector2f(i.getPosition().x, i.getPosition().y - scroll * 10));
        _window->draw(i);
        // j++;
    }
    for (auto i : primitive) {
        // i.setPosition(sf::Vector2f(i.getPosition().x, i.getPosition().y - scroll * 10));
        _window->draw(i);
    }
    for (auto i : light) {
        // i.setPosition(sf::Vector2f(i.getPosition().x, i.getPosition().y - scroll * 10));
        _window->draw(i);
    }
}

void Window::display_text()
{
    for (auto i : div_settings_text) {
        // i.setPosition(sf::Vector2f(i.getPosition().x, i.getPosition().y - scroll * 10));
        _window->draw(i);
    }
}

void Window::execute ()
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    if (path_makefile[0] != '/')
        path_makefile = currentPath.string() + "/" + path_makefile;
    if (path_cfg[0] != '/')
        path_cfg = currentPath.string() + "/" + path_cfg;
    if (path_ppm[0] != '/')
        path_ppm = currentPath.string() + "/" + path_ppm;

    std::string makeCommand = std::string("cd ") + path_makefile + " && " + make;
    std::string raytracerCommand = path_makefile + "raytracer " + path_cfg;
    std::string screenCommand = "cp " + path_makefile + "screen.ppm " + path_ppm;
    std::string convertCommand = "rm -f " + path_ppm + "screen.png" + " && ffmpeg -i " + path_ppm + "screen.ppm " + path_ppm + "screen.png";

    if (!std::system(makeCommand.c_str())) {
        if (!std::system(raytracerCommand.c_str())) {
            if (std::system(screenCommand.c_str())) {
                std::cerr << "Erreur lors de la copy du rendu" << std::endl;
                exit (84);
            } else {
                if (std::system(convertCommand.c_str())) {
                    std::cerr << "Erreur lors de la copy du rendu" << std::endl;
                    exit (84);
                }
            }
        } else {
            std::cerr << "Erreur lors de l'exuction du raytracer" << std::endl;
            exit (84);
        }
    } else {
        std::cerr << "Erreur lors de la compilation make" << std::endl;
        exit (84);
    }
    make = "make";
}

void Window::display_img (sf::Sprite sprite)
{
    sprite.setPosition(div_display.back().getPosition());
    this->_window->draw(sprite);
}

bool Window::is_int_div(std::vector<sf::RectangleShape> vecteur, int i)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    if (mousePosition.x >= vecteur.at(i).getPosition().x &&
     mousePosition.x <= (vecteur.at(i).getPosition().x + vecteur.at(i).getSize().x)
    && mousePosition.y - 1914 >= vecteur.at(i).getPosition().y &&
     mousePosition.y - 1914 <= (vecteur.at(i).getPosition().y + vecteur.at(i).getSize().y))
        return true;
    std::cout << "souris: " << mousePosition.x << " " << mousePosition.y - 1800 << std::endl;
    std::cout << "bouton x: " << vecteur.at(i).getPosition().x << " " << vecteur.at(i).getPosition().x + vecteur.at(i).getSize().x << std::endl;
    std::cout << "bouton y: " << vecteur.at(i).getPosition().y << " " << vecteur.at(i).getPosition().y + vecteur.at(i).getSize().y << std::endl;
    return false;
}

void Window::event()
{
    if (is_int_div(div_settings, div_settings.size() - 1)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            execute();
        div_settings.at(div_settings.size() - 1).setFillColor(SFML_Grey);
    } else
        div_settings.at(div_settings.size() - 1).setFillColor(SFML_Blue_twitter);

    if (is_int_div(div_settings, C_PX)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            execute();
        div_settings.at(C_PX).setFillColor(SFML_Grey_Light);
    } else
        div_settings.at(C_PX).setFillColor(SFML_Grey);

    if (is_int_div(div_settings, ADD_P)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            execute();
        div_settings.at(ADD_P).setFillColor(SFML_Grey_Light);
    } else
        div_settings.at(ADD_P).setFillColor(SFML_Grey);

    if (is_int_div(div_settings, ADD_L)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            execute();
        div_settings.at(ADD_L).setFillColor(SFML_Grey_Light);
    } else
        div_settings.at(ADD_L).setFillColor(SFML_Grey);

    if (is_int_div(div_settings, C_P)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            execute();
        div_settings.at(C_P).setFillColor(SFML_Grey_Light);
    } else
        div_settings.at(C_P).setFillColor(SFML_Grey);

    if (is_int_div(div_settings, C_R)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            execute();
        div_settings.at(C_R).setFillColor(SFML_Grey_Light);
    } else
        div_settings.at(C_R).setFillColor(SFML_Grey);

    if (is_int_div(div_settings, C_FOV)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            execute();
        div_settings.at(C_FOV).setFillColor(SFML_Grey_Light);
    } else
        div_settings.at(C_FOV).setFillColor(SFML_Grey);
}

void Window::display ()
{
    while (this->_window->isOpen())
    {
        sf::Texture texture;
        if (!texture.loadFromFile(path_ppm + "screen.png"))
            std::cout << "error screen.png" << std::endl;
        sf::Sprite sprite(texture);
        sf::Event event;
        while (this->_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->_window->close();
            // if (event.type == sf::Event::MouseWheelScrolled) {
            //     if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            //         if (event.mouseWheelScroll.delta - scroll >= 0)
            //             scroll += event.mouseWheelScroll.delta;
            //             std::cout << "scroll: " << scroll << std::endl;
            //     }
            // }
        }
        init_div();
        this->_window->clear(sf::Color::White);
        this->display_rectangles();
        this->display_text();
        this->display_img(sprite);
        this->event();
        this->_window->display();
        // this->div_settings.clear();
        // this->div_settings_text.clear();
        // this->div_display.clear();
        // this->primitive.clear();
        // this->light.clear();
        // debug();
    }
}