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

bool Raytracer::Sphere::hits(const Ray &ray, maths::Point3D &intersectionPoint) const
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

        if (t1 >= 0) {
            maths::Point3D ori = ray.origin;
            maths::Vector3D dir = ray.direction;
            intersectionPoint = ori + dir * t1;
            return true;
            // maths::Vector3D p2 = {ray.origin.x + t2 * ray.direction.x, ray.origin.y + t2 * ray.direction.y, ray.origin.z + t2 * ray.direction.z};
        }
        if (t2 >= 0) {
            maths::Point3D ori = ray.origin;
            maths::Vector3D dir = ray.direction;
            intersectionPoint = ori + dir * t2;
            // maths::Vector3D p2 = {ray.origin.x + t2 * ray.direction.x, ray.origin.y + t2 * ray.direction.y, ray.origin.z + t2 * ray.direction.z};
        }
    }
    return false;
}