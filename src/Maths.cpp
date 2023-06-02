/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Maths.cpp
*/

#include "Raytracer.hpp"

maths::Point3D::Point3D(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

maths::Point3D::Point3D(const maths::Point3D &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

maths::Point3D &maths::Point3D::operator=(const Point3D &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}

bool maths::Point3D::operator==(const Point3D &other) const
{
    if (this->x == other.x && this->y == other.y && this->z == other.z)
        return true;
    return false;
}

maths::Point3D &maths::Point3D::operator+(const Vector3D &vector)
{
    maths::Point3D *result = new maths::Point3D(
        this->x + vector.x,
        this->y + vector.y,
        this->z + vector.z
    );
    return *result;
}

double maths::Point3D::distanceBetween(const Point3D &other) const
{
    double dx = other.x - x;
    double dy = other.y - y;
    double dz = other.z - z;
    double distance = std::sqrt(dx * dx + dy * dy + dz * dz);

    return distance;
}

maths::Vector3D::Vector3D(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

maths::Vector3D::Vector3D(const maths::Vector3D &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

maths::Vector3D &maths::Vector3D::operator=(const Vector3D &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}

maths::Vector3D &maths::Vector3D::operator+(const Vector3D &other)
{
    maths::Vector3D *result = new maths::Vector3D(
        this->x + other.x,
        this->y + other.y,
        this->z + other.z
    );
    return *result;
}

maths::Vector3D &maths::Vector3D::operator+=(const maths::Vector3D &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

maths::Vector3D &maths::Vector3D::operator-(const maths::Vector3D &other)
{
    maths::Vector3D *result = new maths::Vector3D(
        this->x - other.x,
        this->y - other.y,
        this->z - other.z
    );
    return *result;
}

maths::Vector3D &maths::Vector3D::operator-=(const maths::Vector3D &other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

maths::Vector3D &maths::Vector3D::operator*(const maths::Vector3D &other)
{
    maths::Vector3D *result = new maths::Vector3D(
        this->x * other.x,
        this->y * other.y,
        this->z * other.z
    );
    return *result;
}

maths::Vector3D &maths::Vector3D::operator*=(const maths::Vector3D &other)
{
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
}

maths::Vector3D &maths::Vector3D::operator/(const maths::Vector3D &other)
{
    maths::Vector3D *result = new maths::Vector3D(
        this->x / other.x,
        this->y / other.y,
        this->z / other.z
    );
    return *result;
}

maths::Vector3D &maths::Vector3D::operator/=(const maths::Vector3D &other)
{
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    return *this;
}

maths::Vector3D &maths::Vector3D::operator*(const double value)
{
    maths::Vector3D *result = new maths::Vector3D(
        this->x * value,
        this->y * value,
        this->z * value
    );
    return *result;
}

maths::Vector3D &maths::Vector3D::operator*=(const double value)
{
    this->x *= value;
    this->y *= value;
    this->z *= value;
    return *this;
}

maths::Vector3D &maths::Vector3D::operator/(const double value)
{
    maths::Vector3D *result = new maths::Vector3D(
        this->x / value,
        this->y / value,
        this->z / value
    );
    return *result;
}

maths::Vector3D &maths::Vector3D::operator/=(const double value)
{
    this->x /= value;
    this->y /= value;
    this->z /= value;
    return *this;
}
