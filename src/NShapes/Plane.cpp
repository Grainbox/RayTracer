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

bool Raytracer::Plane::hits(const Ray &ray, maths::Point3D &intersectionPoint, maths::Vector3D &normal) const
{
    double t = 0;

    if (_axis == 'X')
        t = (_axis_pos - ray.origin.x) / ray.direction.x;
    else if (_axis == 'Y')
        t = (_axis_pos - ray.origin.y) / ray.direction.y;
    else if (_axis == 'Z')
        t = (_axis_pos - ray.origin.z) / ray.direction.z;
    
    if (t < 0)
        return false;

    // Calculate intersection point
    maths::Point3D ori = ray.origin;
    maths::Vector3D dir = ray.direction;
    intersectionPoint = ori + dir * t;

    // Calculate normal
    normal = {0, 0, 0};
    if (_axis == 'X') normal.x = 1;
    else if (_axis == 'Y') normal.y = 1;
    else if (_axis == 'Z') normal.z = 1;

    // Check if normal should be flipped (if ray hits the other side)
    // For now, let's keep it simple, but strictly dot(dir, normal) should be < 0
    
    return true;
}

void Raytracer::Plane::setSettings(const libconfig::Setting &settings)
{
    Color color;

    if (settings.exists("axis")) {
        this->_axis = std::string((const char *)settings["axis"])[0];
        this->_axis_pos = settings["axis_pos"];
        color.r = settings["color"][0];
        color.g = settings["color"][1];
        color.b = settings["color"][2];
        this->setColor(color);
        if (settings.exists("reflectivity"))
            this->setReflectivity((double)settings["reflectivity"]);
    }
}