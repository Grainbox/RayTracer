/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** AShape.hpp
*/

#pragma once
#include <shapes/AShape.hpp>

namespace Raytracer {

    class Rectangle : public AShape<Rectangle>
    {
    public:
        Rectangle(void) = default;
        Rectangle(maths::Point3D origin, maths::Vector3D bottow_side,
                maths::Vector3D left_side, Color color);
        Rectangle(const libconfig::Setting &setting);
        ~Rectangle() = default;

        maths::Point3D pointAt(double u, double v);

        maths::Point3D origin;
        maths::Vector3D bottom_side;
        maths::Vector3D left_side;
        // std::shared_ptr<IShape> const clone(const libconfig::Setting &settings) const override {
        //     std::shared_ptr<IShape> thiscp = std::make_shared<Rectangle>(*this);

        //     thiscp->setSettings(settings);
        //     return thiscp;
        // }
        bool hits(const Ray &ray, maths::Point3D &intersectionPoint) const override;
        bool doubleHits(const Ray &ray) const override;
    };
}
