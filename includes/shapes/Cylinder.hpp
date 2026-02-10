/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cylinder.hpp
*/

#pragma once

#include <shapes/AShape.hpp>

namespace Raytracer {
    class Cylinder : public AShape<Cylinder> {
        public:
            Cylinder(void) = default;
            Cylinder(const libconfig::Setting &settings) {
                libconfig::Setting &convert = const_cast<libconfig::Setting &>(settings);
                double radius = 1.0;
                double height = -1.0; // Infinite by default

                if (settings.exists("radius"))
                    radius = (double)settings["radius"];
                if (settings.exists("height"))
                    height = (double)settings["height"];

                if (!convert.exists("size")) {
                    libconfig::Setting &size = convert.add("size", libconfig::Setting::TypeGroup);
                    size.add("x", libconfig::Setting::TypeFloat) = radius;
                    size.add("y", libconfig::Setting::TypeFloat) = height;
                    size.add("z", libconfig::Setting::TypeFloat) = radius;
                }
                AShape::setSettings(convert);
            }
            ~Cylinder() = default;
            bool hits(const Ray &ray, maths::Point3D &intersectionPoint, maths::Vector3D &normal) const override;
            bool doubleHits(const Ray &ray) const override;
    };
}
