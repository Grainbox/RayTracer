/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** AShape.hpp
*/

#pragma once

#include <shapes/IShape.hpp>
#include <memory>
#include "libconfig.h++"

namespace Raytracer {
    template <typename ShapeType>
    class AShape : public IShape {
    public:
        AShape(void) = default;
        AShape(const libconfig::Setting &setting);

        Color getColor() const override;
        double getReflectivity() const override;
        double getTransparency() const override;
        double getRefractiveIndex() const override;
        maths::Point3D getCenter() const override;
        maths::Vector3D getSize() const override;

        void setColor(Color color) override;
        void setReflectivity(double reflectivity) override;
        void setTransparency(double transparency) override;
        void setRefractiveIndex(double refractiveIndex) override;
        void setCenter(maths::Point3D center) override;
        void setSize(maths::Vector3D size) override;
        void setSettings(const libconfig::Setting &settings) override;

        std::shared_ptr<IShape> const clone() const override;
    protected:
        maths::Point3D center;
        maths::Vector3D size;
        Color color;
        double reflectivity = 0.0;
        double transparency = 0.0;
        double refractiveIndex = 1.0;
    };
}