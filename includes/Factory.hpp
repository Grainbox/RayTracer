/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Factory.hpp
*/

#pragma once

#include "Raytracer.hpp"
#include <functional>
#include <libconfig.h++>
#include <map>
#include <memory>
#include <shapes/IShape.hpp>

namespace Raytracer
{
     class SFactory
    {
        private:
        using ShapeConstructor = std::function<std::shared_ptr<IShape>(const libconfig::Setting &)>;
        std::map<std::string, ShapeConstructor> _shapeMap;

        public:
            SFactory(void) noexcept;
            ~SFactory() = default;

            void addShape(std::string name, ShapeConstructor constructor) {
                std::cout << "[Factory init] Adding shape: " << name << std::endl;
                _shapeMap.insert(std::pair<std::string, ShapeConstructor>(name, constructor));
            }
            std::shared_ptr<IShape> const createShape(std::string name, const libconfig::Setting &settings) const {
                std::cout << "> Creating shape: " << name << std::endl;
                auto constructor = _shapeMap.at(name);
                std::shared_ptr<IShape> shape = constructor(settings);
                return shape;
            }
    };
}