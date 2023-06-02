/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** raytracer
*/

#include "Raytracer.hpp"

RayTracer::Ray::Ray(maths::Point3D point, maths::Vector3D vector)
{
    this->origin = point;
    this->direction = vector;
}

RayTracer::Ray::Ray(Ray &other)
{
    this->origin = other.origin;
    this->direction = other.direction;
}

RayTracer::Ray &RayTracer::Ray::operator=(Ray &other)
{
    this->origin = other.origin;
    this->direction = other.direction;
    return *this;
}

RayTracer::Sphere::Sphere(maths::Point3D center, double radius)
{
    this->center = center;
    this->radius = radius;
}

RayTracer::Sphere::Sphere(RayTracer::Sphere &other)
{
    this->center = other.center;
    this->radius = other.radius;
}

RayTracer::Sphere &RayTracer::Sphere::operator=(RayTracer::Sphere &other)
{
    this->center = other.center;
    this->radius = other.radius;
    return *this;
}

bool RayTracer::Sphere::hits(RayTracer::Ray ray) const
{
    maths::Vector3D oc;

    oc.x = ray.origin.x - center.x;
    oc.y = ray.origin.y - center.y;
    oc.z = ray.origin.z - center.z;

    double a = std::pow(ray.direction.x, 2) + pow(ray.direction.y, 2) + pow(ray.direction.z, 2);
    double b = 2 * (oc.x * ray.direction.x + oc.y * ray.direction.y + oc.z * ray.direction.z);
    double c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - pow(radius, 2);

    double discriminant = std::pow(b, 2)- 4 * a * c;

    if (discriminant >= 0) {
        double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        double t2 = (-b + std::sqrt(discriminant)) / (2 * a);

        if (t1 >= 0)
            return true;
        // maths::Vector3D p1 = {ray.origin.x + t1 * ray.direction.x, ray.origin.y + t1 * ray.direction.y, ray.origin.z + t1 * ray.direction.z};
        if (t2 >= 0)
            return true;
        // maths::Vector3D p2 = {ray.origin.x + t2 * ray.direction.x, ray.origin.y + t2 * ray.direction.y, ray.origin.z + t2 * ray.direction.z};
    }
    return false;
}

RayTracer::Rectangle::Rectangle(maths::Point3D origin, maths::Vector3D bottow_side,
maths::Vector3D left_side)
{
    this->origin = origin;
    this->bottow_side = bottow_side;
    this->left_side = left_side;
}

RayTracer::Rectangle::Rectangle(RayTracer::Rectangle &other)
{
    this->origin = other.origin;
    this->bottow_side = other.bottow_side;
    this->left_side = other.left_side;
}

maths::Point3D RayTracer::Rectangle::pointAt(double u, double v)
{
    maths::Point3D point;

    point.x = origin.x + u;
    point.y = origin.y + v;
    point.z = origin.z;
    return point;
}

RayTracer::Camera::Camera(void)
{
    origin.x = 0;
    origin.y = 0;
    origin.z = 0;
}

RayTracer::Ray RayTracer::Camera::ray(double u, double v)
{
    RayTracer::Ray ray;
    maths::Point3D point = screen.pointAt(u, v);
    
    ray.origin = origin;
    ray.direction.x = point.x - origin.x;
    ray.direction.y = point.y - origin.y;
    ray.direction.z = point.z - origin.z;
    return ray;
}
