/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** AShape.hpp
*/

#pragma once

#include <shapes/AShape.hpp>

namespace Raytracer {
    class Sphere : public AShape<Sphere> {
        public:
            Sphere(void) = default;
            Sphere(const libconfig::Setting &settings) {
                std::cout << "Sphere constructor" << std::endl;
                libconfig::Setting &convert = const_cast<libconfig::Setting &>(settings);
                if (settings.exists("radius")) {
                    int radius = settings["radius"];
                    convert.remove("radius");
                    libconfig::Setting &size = convert.add("size", libconfig::Setting::TypeGroup);
                    size.add("x", libconfig::Setting::TypeFloat) = radius;
                    size.add("y", libconfig::Setting::TypeFloat) = radius;
                    size.add("z", libconfig::Setting::TypeFloat) = radius;
                }
                std::cout << "Sphere constructor end" << std::endl;
                AShape::setSettings(convert);
            }
            ~Sphere() = default;
            bool hits(const Ray &ray, maths::Point3D &intersectionPoint) const override;
            bool doubleHits(const Ray &ray) const override;
    };
}
