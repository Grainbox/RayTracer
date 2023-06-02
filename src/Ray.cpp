/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Ray.cpp
*/

#include "Raytracer.hpp"
#include "Maths.hpp"

Raytracer::Ray::Ray(maths::Point3D point, maths::Vector3D vector)
{
    this->origin = point;
    this->direction = vector;
}

Raytracer::Ray::Ray(Ray &other)
{
    this->origin = other.origin;
    this->direction = other.direction;
}

Raytracer::Ray &Raytracer::Ray::operator=(Ray &other)
{
    this->origin = other.origin;
    this->direction = other.direction;
    return *this;
}
