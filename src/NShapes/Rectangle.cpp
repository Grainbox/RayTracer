/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Rectanble.cpp
*/

#include <shapes/Rectangle.hpp>

Raytracer::Rectangle::Rectangle(maths::Point3D origin, maths::Vector3D bottom_side,
    maths::Vector3D left_side, Color color)
{
    this->origin = origin;
    this->bottom_side = bottom_side;
    this->left_side = left_side;
    this->color = color;
}

Raytracer::Rectangle::Rectangle(const libconfig::Setting &setting)
{
    origin.x = setting["origin"][0];
    origin.y = setting["origin"][1];
    origin.z = setting["origin"][2];

    color.r = setting["color"][0];
    color.g = setting["color"][1];
    color.b = setting["color"][2];
}

maths::Point3D Raytracer::Rectangle::pointAt(double u, double v)
{
    maths::Point3D point;

    point.x = origin.x + u;
    point.y = origin.y + v;
    point.z = origin.z;
    return point;
}

bool Raytracer::Rectangle::doubleHits(const Ray &ray) const
{
    //todo
    (void)ray;
    return false;
}

bool Raytracer::Rectangle::hits(const Ray &ray, maths::Point3D &intersectionPoint) const
{
    (void)ray;
    (void)intersectionPoint;
    // todo
    std::cerr << "Rectangle::hits() not implemented" << std::endl;
    return false;
}
