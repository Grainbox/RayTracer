/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Raytacer.hpp
*/

#pragma once

#include <Maths.hpp>
#include "libconfig.h++"
#include <shapes/Rectangle.hpp>
#include <Ray.hpp>
#include <cmath>

struct Color {
    float r, g, b;
};

typedef char axis; // X, Y, Z

namespace Raytracer
{
    class ALight {
        protected:
            maths::Point3D _origin;
        public:
            ALight(maths::Point3D origin) : _origin(origin) {};
            virtual ~ALight() = default;
            maths::Point3D getOrigin() const { return _origin; };
    };

    class PointLight : public ALight {
        public:
            PointLight(maths::Point3D origin) : ALight(origin) {};
            ~PointLight() = default;
    };

    class DirectionalLight : public PointLight {
        private:
            maths::Vector3D _direction;
        public:
            DirectionalLight(maths::Point3D origin, maths::Vector3D direction) : PointLight(origin), _direction(direction) {};
            ~DirectionalLight() = default;
            maths::Vector3D getDirection() const { return _direction; };
    };
    // Abstract Shape class

    class Camera {
        public:
            Camera(void);
            Camera(maths::Point3D position, maths::Vector3D direction, float FOV, int width, int height);
            ~Camera() = default;
            // maths::Point3D origin;
            // Raytracer::Rectangle screen;
            Camera &operator=(const Camera &other);
            Raytracer::Ray ray(double u, double v);
            int getWidth() const;
            int getHeight() const;
            Rectangle getScreen();
        private:
            maths::Point3D _origin; // position
            maths::Vector3D _direction;
            Rectangle _screen;
            float _fov;
            int _width;
            int _height;
    };
}
