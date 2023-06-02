#pragma once
#include <Maths.hpp>

namespace Raytracer
{
    class Ray
    {
    public:
        Ray(void) = default;
        Ray(maths::Point3D point, maths::Vector3D vector);
        Ray(Ray &other);
        ~Ray() = default;

        maths::Point3D origin;
        maths::Vector3D direction;

        Ray &operator=(Ray &other);
    };
}
