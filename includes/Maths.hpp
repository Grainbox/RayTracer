/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Parser.hpp
*/

#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>

namespace maths 
{
    class Vector3D {
        public:
            Vector3D(void) = default;
            Vector3D(double x, double y, double z);
            Vector3D(const Vector3D &other);
            ~Vector3D() = default;

            double x;
            double y;
            double z;

            double length() const
            { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); };

            Vector3D &operator=(const Vector3D &other);

            Vector3D &operator+(const Vector3D &other);
            Vector3D &operator+=(const Vector3D &other);
            Vector3D &operator-(const Vector3D &other);
            Vector3D &operator-=(const Vector3D &other);
            Vector3D &operator*(const Vector3D &other);
            Vector3D &operator*=(const Vector3D &other);
            Vector3D &operator/(const Vector3D &other);
            Vector3D &operator/=(const Vector3D &other);

            Vector3D &operator*(const double value);
            Vector3D &operator*=(const double value);
            Vector3D &operator/(const double value);
            Vector3D &operator/=(const double value);

        private:
    };

    class Point3D {
        public:
            Point3D(void) = default;
            Point3D(double x, double y, double z);
            Point3D(const Point3D &other);
            ~Point3D() = default;

            double x;
            double y;
            double z;

            Point3D &operator=(const Point3D &other);
            bool operator==(const Point3D &other) const;

            Point3D &operator+(const Vector3D &vector);
            double distanceBetween(const Point3D &other) const;

        private:
    };

} // namespace maths