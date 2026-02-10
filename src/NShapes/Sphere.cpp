/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Sphere.cpp
*/

#include <shapes/Sphere.hpp>

// std::vector<maths::Vector3D>


bool Raytracer::Sphere::doubleHits(const Ray &ray) const
{
    maths::Vector3D oc;

    oc.x = ray.origin.x - center.x;
    oc.y = ray.origin.y - center.y;
    oc.z = ray.origin.z - center.z;

    double radius = this->getSize().x;

    double a = std::pow(ray.direction.x, 2) + pow(ray.direction.y, 2) + pow(ray.direction.z, 2);
    double b = 2 * (oc.x * ray.direction.x + oc.y * ray.direction.y + oc.z * ray.direction.z);
    double c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - pow(radius, 2);

    double discriminant = std::pow(b, 2) - 4 * a * c;

    if (discriminant >= 0)
    {
        double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        double t2 = (-b + std::sqrt(discriminant)) / (2 * a);

        if (t1 >= 0 && t2 >= 0) {
            return true;
        }
        return false;
    }
    return false;
}

bool Raytracer::Sphere::hits(const Ray &ray, maths::Point3D &intersectionPoint, maths::Vector3D &normal) const
{
    maths::Vector3D oc;

    oc.x = ray.origin.x - center.x;
    oc.y = ray.origin.y - center.y;
    oc.z = ray.origin.z - center.z;

    double radius = this->getSize().x;

    double a = std::pow(ray.direction.x, 2) + pow(ray.direction.y, 2) + pow(ray.direction.z, 2);
    double b = 2 * (oc.x * ray.direction.x + oc.y * ray.direction.y + oc.z * ray.direction.z);
    double c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - pow(radius, 2);

    double discriminant = std::pow(b, 2) - 4 * a * c;

    if (discriminant >= 0)
    {
        double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        double t2 = (-b + std::sqrt(discriminant)) / (2 * a);

        double t = -1.0;
        if (t1 >= 0) {
            t = t1;
        } else if (t2 >= 0) {
            t = t2;
        }

        if (t >= 0) {
            maths::Point3D ori = ray.origin;
            maths::Vector3D dir = ray.direction;
            intersectionPoint = ori + dir * t;
            
            // Calculate normal
            normal.x = intersectionPoint.x - center.x;
            normal.y = intersectionPoint.y - center.y;
            normal.z = intersectionPoint.z - center.z;
            double len = normal.length();
            if (len > 0) normal /= len;
            
            return true;
        }
    }
    return false;
}