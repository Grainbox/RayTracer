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
    
    // Normalize ray direction
    double rayLen = std::sqrt(ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z);
    if (rayLen > 0) {
        ray.direction.x /= rayLen;
        ray.direction.y /= rayLen;
        ray.direction.z /= rayLen;
    }

    Color pixelColor = {0, 0, 0};
    
    // Find closest hit
    std::shared_ptr<IShape> closestShape = nullptr;
    double closestDist = 1e20; // Infinity
    maths::Point3D closestInters;
    maths::Vector3D closestNormal;

    for (auto &shape : shapes) {
        maths::Point3D inters;
        maths::Vector3D normal;
        if (shape->hits(ray, inters, normal)) {
            double dist = inters.distanceBetween(ray.origin);
            if (dist < closestDist) {
                closestDist = dist;
                closestShape = shape;
                closestInters = inters;
                closestNormal = normal;
            }
        }
    }

    if (closestShape) {
        Color objColor = closestShape->getColor();
        
        // Very low ambient for strong shadow contrast
        double ambientFactor = (this->ambient > 0) ? this->ambient * 0.15 : 0.05;
        
        double r = objColor.r * ambientFactor;
        double g = objColor.g * ambientFactor;
        double b = objColor.b * ambientFactor;

        double diffuseFactor = (this->diffuse > 0) ? this->diffuse : 0.8;
        double specularStrength = 0.6;
        double shininess = 32.0; // Phong exponent

        for (auto &light : lights) {
            maths::Vector3D lightDir;
            double attenuation = 1.0;
            
            if (auto dLight = std::dynamic_pointer_cast<DirectionalLight>(light)) {
                lightDir = dLight->getDirection();
                lightDir.x *= -1; lightDir.y *= -1; lightDir.z *= -1; 
            } else if (auto pLight = std::dynamic_pointer_cast<PointLight>(light)) {
                maths::Point3D lightPos = pLight->getOrigin();
                lightDir.x = lightPos.x - closestInters.x;
                lightDir.y = lightPos.y - closestInters.y;
                lightDir.z = lightPos.z - closestInters.z;
                
                double lightDist = std::sqrt(lightDir.x*lightDir.x + lightDir.y*lightDir.y + lightDir.z*lightDir.z);
                attenuation = 1.0 / (1.0 + 0.0003 * lightDist * lightDist);
            }

            // Normalize LightDir
            double len = std::sqrt(lightDir.x*lightDir.x + lightDir.y*lightDir.y + lightDir.z*lightDir.z);
            if (len > 0) {
                lightDir.x /= len; lightDir.y /= len; lightDir.z /= len;
            }

            // Diffuse (Lambertian)
            double dot = closestNormal.x * lightDir.x + closestNormal.y * lightDir.y + closestNormal.z * lightDir.z;
            
            if (dot > 0) {
                r += objColor.r * diffuseFactor * dot * attenuation;
                g += objColor.g * diffuseFactor * dot * attenuation;
                b += objColor.b * diffuseFactor * dot * attenuation;

                // Specular (Phong reflection)
                // Reflect light direction: R = 2*(N.L)*N - L
                double rx = 2.0 * dot * closestNormal.x - lightDir.x;
                double ry = 2.0 * dot * closestNormal.y - lightDir.y;
                double rz = 2.0 * dot * closestNormal.z - lightDir.z;

                // View direction (from intersection to camera)
                double vx = ray.origin.x - closestInters.x;
                double vy = ray.origin.y - closestInters.y;
                double vz = ray.origin.z - closestInters.z;
                double vLen = std::sqrt(vx*vx + vy*vy + vz*vz);
                if (vLen > 0) { vx /= vLen; vy /= vLen; vz /= vLen; }

                double specDot = rx*vx + ry*vy + rz*vz;
                if (specDot > 0) {
                    double specFactor = specularStrength * std::pow(specDot, shininess) * attenuation;
                    r += 255 * specFactor;
                    g += 255 * specFactor;
                    b += 255 * specFactor;
                }
            }
        }

        // Clamp
        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;

        pixelColor.r = r;
        pixelColor.g = g;
        pixelColor.b = b;
    }
    // else: black background

    return pixelColor;
}

