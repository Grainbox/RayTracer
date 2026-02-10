/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Camera.cpp
*/

#define _USE_MATH_DEFINES
#include "Maths.hpp"
#include "Raytracer.hpp"

Raytracer::Camera::Camera(void)
{
    _origin.x = 0;
    _origin.y = 0;
    _origin.z = 0;
}

Raytracer::Camera::Camera(maths::Point3D position, maths::Vector3D direction, float fov, int width, int height)
{
    maths::Vector3D bottom_side = maths::Vector3D(0, width, 0);
    maths::Vector3D left_side = maths::Vector3D(0, height, 0);
    Color color = {0, 0, 0};
    this->_origin = position;
    this->_direction = direction;
    this->_fov = fov;
    this->_width = width;
    this->_height = height;
    float fovRadians = fov * (M_PI / 180.0f);
    float halfFov = fovRadians / 2.0f;
    float distanceWidth = (0.5f * width) / std::tan(halfFov);
    float distanceHeight = (0.5f * height) / std::tan(halfFov);
    float distance = std::max(distanceWidth, distanceHeight);
    maths::Point3D screen_origin = maths::Point3D(_origin.x - width / 2, _origin.y - height / 2, _origin.z - distance);
    this->_screen = Rectangle(screen_origin, bottom_side, left_side, color);
}

Raytracer::Camera &Raytracer::Camera::operator=(const Camera &other)
{
    if (this != &other) {
        _origin = other._origin;
        _direction = other._direction;
        _fov = other._fov;
        _width = other._width;
        _height = other._height;
        _screen = other._screen;
    }
    return *this;
}

Raytracer::Ray Raytracer::Camera::ray(double u, double v)
{
    // We invert v to match standard image coordinates (Top-Left 0,0) with World Up (+Y)
    // Pixel 0 (Top) -> High Y (World Up)
    // Pixel Height (Bottom) -> Low Y (World Down)
    maths::Point3D point = _screen.pointAt(u, _height - v);
    
    Raytracer::Ray r;
    r.origin = _origin;
    r.direction.x = point.x - _origin.x;
    r.direction.y = point.y - _origin.y;
    r.direction.z = point.z - _origin.z;
    return r;
}

int Raytracer::Camera::getHeight() const
{
    return this->_height;
}

int Raytracer::Camera::getWidth() const
{
    return this->_width;
}

Raytracer::Rectangle Raytracer::Camera::getScreen()
{
    return this->_screen;
}
