#include <shapes/AShape.hpp>
#include <shapes/Rectangle.hpp>
#include <shapes/Sphere.hpp>
#include <shapes/Plane.hpp>

template <typename ShapeType>
Raytracer::AShape<ShapeType>::AShape(const libconfig::Setting &setting)
{
    AShape::setSettings(setting);
}

template <typename ShapeType>
Raytracer::Color Raytracer::AShape<ShapeType>::getColor() const
{
    return this->color;
}

template <typename ShapeType>
maths::Point3D Raytracer::AShape<ShapeType>::getCenter() const
{
    return this->center;
}

template <typename ShapeType>
maths::Vector3D Raytracer::AShape<ShapeType>::getSize() const
{
    return this->size;
}

template <typename ShapeType>
void Raytracer::AShape<ShapeType>::setColor(Raytracer::Color color)
{
    this->color = color;
}

template <typename ShapeType>
void Raytracer::AShape<ShapeType>::setCenter(maths::Point3D center)
{
    this->center = center;
}

template <typename ShapeType>
void Raytracer::AShape<ShapeType>::setSize(maths::Vector3D size)
{
    this->size = size;
}

template <typename ShapeType>
void Raytracer::AShape<ShapeType>::setSettings(const libconfig::Setting &settings)
{
    try {
        this->center = {settings["center"][0], settings["center"][1], settings["center"][2]};
        this->size = {settings["size"][0], settings["size"][1], settings["size"][2]};
        this->color = {settings["color"][0], settings["color"][1], settings["color"][2]};
    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << nfex.what() << std::endl;
    }
}

template <typename ShapeType>
std::shared_ptr<Raytracer::IShape> const Raytracer::AShape<ShapeType>::clone(void) const
{
    std::shared_ptr<Raytracer::IShape> thiscp = std::make_shared<ShapeType>(static_cast<ShapeType const &>(*this));
    return thiscp;
}

template class Raytracer::AShape<Raytracer::Rectangle>;
template class Raytracer::AShape<Raytracer::Sphere>;
template class Raytracer::AShape<Raytracer::Plane>;