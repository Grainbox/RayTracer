/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Plane.hpp
*/

#pragma once

#include <shapes/AShape.hpp>

namespace Raytracer {
    class Plane : public AShape<Plane> {
    public:
        Plane(void) = default;
        Plane(const libconfig::Setting &settings);
        ~Plane() = default;
        bool hits(const Ray &ray, maths::Point3D &intersectionPoint) const override;
        bool doubleHits(const Ray &ray) const override;
        void setSettings(const libconfig::Setting &settings) override;

    private:
        char _axis;
        int _axis_pos;
    };
}