/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Cylinder.cpp
*/

#include <shapes/Cylinder.hpp>
#include <cmath>

bool Raytracer::Cylinder::doubleHits(const Ray &ray) const
{
    // Simplified for now
    return false;
}

bool Raytracer::Cylinder::hits(const Ray &ray, maths::Point3D &intersectionPoint, maths::Vector3D &normal) const
{
    // Cylinder along Y axis: (x - cx)^2 + (z - cz)^2 = r^2
    double radius = this->getSize().x;
    double height = this->getSize().y;
    
    double ox = ray.origin.x - center.x;
    double oz = ray.origin.z - center.z;
    
    double dx = ray.direction.x;
    double dz = ray.direction.z;
    
    double a = dx * dx + dz * dz;
    double b = 2.0 * (ox * dx + oz * dz);
    double c = ox * ox + oz * oz - radius * radius;
    
    if (std::abs(a) < 1e-6) return false;
    
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0) return false;
    
    double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);
    
    double t = -1.0;
    if (t1 >= 0) {
        // Check height for t1
        double y = ray.origin.y + t1 * ray.direction.y;
        if (height < 0 || (y >= center.y - height / 2.0 && y <= center.y + height / 2.0))
            t = t1;
    }
    
    if (t < 0 && t2 >= 0) {
        // Check height for t2
        double y = ray.origin.y + t2 * ray.direction.y;
        if (height < 0 || (y >= center.y - height / 2.0 && y <= center.y + height / 2.0))
            t = t2;
    }
    
    if (t >= 0) {
        maths::Point3D ori = ray.origin;
        maths::Vector3D dir = ray.direction;
        intersectionPoint = ori + dir * t;
        normal.x = intersectionPoint.x - center.x;
        normal.y = 0;
        normal.z = intersectionPoint.z - center.z;
        double len = normal.length();
        if (len > 0) normal /= len;
        return true;
    }
    
    return false;
}
