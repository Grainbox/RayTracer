/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Parser.hpp
*/

#include "Scene.hpp"

void Raytracer::Scene::addLight(std::shared_ptr<ALight> light)
{
    lights.push_back(std::move(light));
}

void Raytracer::Scene::addShape(const std::shared_ptr<IShape> shape)
{
    shapes.push_back(shape);
}

void Raytracer::Scene::setCamera(const Camera &camera)
{
    this->camera = camera;
    // printf("%f\n", this->camera.getScreen().origin.x);
}

std::string Raytracer::Scene::render()
{
    int height = camera.getHeight();
    int width = camera.getWidth();
    int max_pixel_val = 255;

    std::string frame =
        "P3 " + std::to_string(width) + " " + std::to_string(height) +
        " " + std::to_string(max_pixel_val) + "\n"; // Header

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Color color = this->getColor(j, i);
            frame += std::to_string((int)color.r);
            frame += " ";
            frame += std::to_string((int)color.g);
            frame += " ";
            frame += std::to_string((int)color.b);
            frame += " ";
        }
    }
    return frame;
}

Raytracer::Color Raytracer::Scene::getColor(int x, int y)
{
    Raytracer::Ray ray = camera.ray(x, y);
    Color pixelColor = {0, 0, 0};
    bool doubleHit = false;
    maths::Point3D inters;

    for (auto it : shapes) {
        // if (it.get()->doubleHits(ray))
        //     doubleHit = true;
        if (it.get()->hits(ray, inters)) {
            if (it.get()->doubleHits(ray))
                doubleHit = true;
            // onShape = true;
            pixelColor = it.get()->getColor();
            for (auto it2 : lights) {
                if (std::dynamic_pointer_cast<DirectionalLight>(it2)) {
                    ;
                } else if (std::dynamic_pointer_cast<PointLight>(it2)) {
                    // printf("da\n");
                    maths::Point3D lightOrig = it2.get()->getOrigin();
                    maths::Vector3D lightVector(inters.x - lightOrig.x, inters.y - lightOrig.y, inters.z - lightOrig.z);
                    Raytracer::Ray lightRay(lightOrig, lightVector);
                    if (!doubleHit) {
                        // printf("ok\n");
                        double distance = inters.distanceBetween(lightOrig);
                        pixelColor.r += (distance) / 1 * this->diffuse;
                        pixelColor.g += (distance) / 1 * this->diffuse;
                        pixelColor.b += (distance) / 1 * this->diffuse;
                        // printf("r: %f  g: %f  b: %f\n", pixelColor.r, pixelColor.g, pixelColor.b);
                    }
                }
            }
            break;
        }
    }
    return pixelColor;
}
