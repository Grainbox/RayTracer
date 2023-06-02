#include <shapes/Plane.hpp>

Raytracer::Plane::Plane(const libconfig::Setting &settings)
{
    setSettings(settings);
}

bool Raytracer::Plane::doubleHits(const Ray &ray) const
{
    (void)ray;
    return false;
}

bool Raytracer::Plane::hits(const Ray &ray, maths::Point3D &intersectionPoint) const
{
    double t = 0;
    (void)intersectionPoint;

    if (_axis == 'X')
        t = (_axis_pos - ray.origin.x) / ray.direction.x;
    else if (_axis == 'Y')
        t = (_axis_pos - ray.origin.y) / ray.direction.y;
    else if (_axis == 'Z')
        t = (_axis_pos - ray.origin.z) / ray.direction.z;
    if (t < 0)
        return false;
    return true;
}

void Raytracer::Plane::setSettings(const libconfig::Setting &settings)
{
    Color color;

    if (settings.exists("axis")) {
        this->_axis = std::string(settings["axis"])[0];
        this->_axis_pos = settings["axis_pos"];
        color.r = settings["color"][0];
        color.g = settings["color"][1];
        color.b = settings["color"][2];
        this->setColor(color);
    }
}