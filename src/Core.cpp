/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-mathieu.rio
** File description:
** Core
*/

#include "Core.hpp"

Raytracer::Core::Core(std::string config_path) : _config(config_path)
{
    Scene scene = this->_config.getScene();
    std::string frame = scene.render();

    std::ofstream myfile;
    myfile.open ("screen.ppm");
    myfile << frame;
    myfile.close();
}

Raytracer::Core::~Core()
{
}
