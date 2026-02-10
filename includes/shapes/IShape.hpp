
/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** IShape.hpp
*/

#pragma once
#include <Maths.hpp>
#include <Ray.hpp>
#include <memory>
#include <libconfig.h++>

namespace Raytracer
{
    struct Color {
        int r, g, b;
    };
    class Ray;

    class IShape {
        public:
            virtual ~IShape() = default;

            // getters
            virtual bool hits(const Ray &ray, maths::Point3D &intersectionPoint, maths::Vector3D &normal) const = 0;
            virtual bool doubleHits(const Ray &ray) const = 0;
            virtual Color getColor() const = 0;
            virtual double getReflectivity() const = 0;
            virtual double getTransparency() const = 0;
            virtual double getRefractiveIndex() const = 0;
            virtual maths::Point3D getCenter() const = 0;
            virtual maths::Vector3D getSize() const = 0;
            // setters
            virtual void setSettings(const libconfig::Setting &settings) = 0;
            virtual void setColor(Color color) = 0;
            virtual void setReflectivity(double reflectivity) = 0;
            virtual void setTransparency(double transparency) = 0;
            virtual void setRefractiveIndex(double refractiveIndex) = 0;
            virtual void setCenter(maths::Point3D center) = 0;
            virtual void setSize(maths::Vector3D size) = 0;
            virtual std::shared_ptr<IShape> const clone() const = 0;
    };
}