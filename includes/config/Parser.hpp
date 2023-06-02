/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Parser.hpp
*/

#pragma once

#include <iostream>
#include <libconfig.h++>
#include <memory>
#include "Scene.hpp"
#include "Factory.hpp"

namespace Raytracer {
    namespace Parser {
        class ConfigParser {
            public:
                ConfigParser(void) {};
                ConfigParser(const std::string &path);
                ~ConfigParser() = default;

                void parse(const std::string &path);

                libconfig::Config &getConfig(void);
                libconfig::Setting &getRoot(void);
                Scene &getScene(void) { return _scene; };
            private:
                std::string _path = "";
                libconfig::Config _config;
                Scene _scene;
                SFactory _factory;

                void setScene(const libconfig::Setting &root);
                void setSceneCamera(const libconfig::Setting &camera);
                void setScenePrimitives(const libconfig::Setting &primitives);
                void setSceneLights(const libconfig::Setting &lights);
        };
    }
};