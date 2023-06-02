/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Factory.hpp
*/

#include <Factory.hpp>
#include <shapes/Sphere.hpp>
#include <shapes/Rectangle.hpp>
#include <shapes/Plane.hpp>

Raytracer::SFactory::SFactory(void) noexcept
{
    addShape("spheres", [](const libconfig::Setting &settings) -> std::shared_ptr<IShape> {
    return std::make_shared<Sphere>(settings);
    });
    addShape("rectangles", [](const libconfig::Setting &settings) -> std::shared_ptr<IShape> {
        return std::make_shared<Rectangle>(settings);
    });
    addShape("planes", [](const libconfig::Setting &settings) -> std::shared_ptr<IShape> {
        return std::make_shared<Plane>(settings);
    });
}