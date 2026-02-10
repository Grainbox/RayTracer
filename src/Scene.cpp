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

#include <thread>
#include <mutex>

std::string Raytracer::Scene::render()
{
    int height = camera.getHeight();
    int width = camera.getWidth();
    int max_pixel_val = 255;
    
    // Intermediate buffer to store colors
    std::vector<Color> pixels(width * height);
    
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 1;

    std::cout << "Rendering with " << numThreads << " threads..." << std::endl;
    
    std::vector<std::thread> threads;
    int rowsPerThread = height / numThreads;
    
    for (unsigned int t = 0; t < numThreads; ++t) {
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? height : (t + 1) * rowsPerThread;
        
        threads.emplace_back([this, startRow, endRow, width, &pixels]() {
            for (int i = startRow; i < endRow; ++i) {
                for (int j = 0; j < width; ++j) {
                    pixels[i * width + j] = this->getColor(j, i);
                }
            }
        });
    }

    for (auto &t : threads) {
        t.join();
    }

    // Assemble final string
    std::string frame = "P3\n" + std::to_string(width) + " " + std::to_string(height) + "\n" + std::to_string(max_pixel_val) + "\n";
    
    // Reserve space for speed (estimated 4 chars per color component + spaces)
    frame.reserve(frame.size() + width * height * 12);

    for (const auto &color : pixels) {
        frame += std::to_string((int)color.r) + " " + 
                 std::to_string((int)color.g) + " " + 
                 std::to_string((int)color.b) + " ";
    }
    
    return frame;
}

#include <random>

Raytracer::Color Raytracer::Scene::getColor(int x, int y)
{
    if (this->samples <= 1) {
        Raytracer::Ray ray = camera.ray(x, y);
        
        // Normalize ray direction
        double rayLen = std::sqrt(ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z);
        if (rayLen > 0) {
            ray.direction.x /= rayLen;
            ray.direction.y /= rayLen;
            ray.direction.z /= rayLen;
        }

        return getColor(ray, 0);
    }

    // Supersampling (Anti-Aliasing)
    Color finalColor = {0, 0, 0};
    static std::mt19937 gen(std::hash<std::thread::id>{}(std::this_thread::get_id()));
    std::uniform_real_distribution<double> dist(-0.5, 0.5);

    for (int s = 0; s < this->samples; s++) {
        double offsetX = dist(gen);
        double offsetY = dist(gen);
        
        Raytracer::Ray ray = camera.ray(x + offsetX, y + offsetY);
        
        double rayLen = std::sqrt(ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z);
        if (rayLen > 0) {
            ray.direction.x /= rayLen;
            ray.direction.y /= rayLen;
            ray.direction.z /= rayLen;
        }

        Color c = getColor(ray, 0);
        finalColor.r += c.r;
        finalColor.g += c.g;
        finalColor.b += c.b;
    }

    finalColor.r /= this->samples;
    finalColor.g /= this->samples;
    finalColor.b /= this->samples;

    return finalColor;
}

Raytracer::Color Raytracer::Scene::getColor(const Raytracer::Ray &ray, int depth)
{
    if (depth >= MAX_DEPTH)
        return {0, 0, 0};

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
        double reflectivity = closestShape->getReflectivity();
        
        // Ambient Light
        double ambientFactor = (this->ambient > 0) ? this->ambient : 0.1;
        
        double r = objColor.r * ambientFactor;
        double g = objColor.g * ambientFactor;
        double b = objColor.b * ambientFactor;

        double diffuseFactor = (this->diffuse > 0) ? this->diffuse : 0.8;
        double specularStrength = 0.6;
        double shininess = 32.0; // Phong exponent

        for (auto &light : lights) {
            maths::Vector3D lightDir;
            double attenuation = 1.0;
            double distanceToLight = 1e20; // Infinity
            
            if (auto dLight = std::dynamic_pointer_cast<DirectionalLight>(light)) {
                lightDir = dLight->getDirection();
                lightDir.x *= -1; lightDir.y *= -1; lightDir.z *= -1; 
            } else if (auto pLight = std::dynamic_pointer_cast<PointLight>(light)) {
                maths::Point3D lightPos = pLight->getOrigin();
                lightDir.x = lightPos.x - closestInters.x;
                lightDir.y = lightPos.y - closestInters.y;
                lightDir.z = lightPos.z - closestInters.z;
                
                distanceToLight = std::sqrt(lightDir.x*lightDir.x + lightDir.y*lightDir.y + lightDir.z*lightDir.z);
                attenuation = 1.0 / (1.0 + 0.0001 * distanceToLight * distanceToLight); // Reduced attenuation slightly
            }

            // Normalize LightDir
            double len = std::sqrt(lightDir.x*lightDir.x + lightDir.y*lightDir.y + lightDir.z*lightDir.z);
            if (len > 0) {
                lightDir.x /= len; lightDir.y /= len; lightDir.z /= len;
            }

            // Shadows with transparency support
            Raytracer::Ray shadowRay(
                maths::Point3D(closestInters.x + closestNormal.x * 0.001, 
                               closestInters.y + closestNormal.y * 0.001, 
                               closestInters.z + closestNormal.z * 0.001),
                lightDir
            );

            double lightTransmission = 1.0;
            for (auto &shape : shapes) {
                maths::Point3D shadowInters;
                maths::Vector3D shadowNormal;
                if (shape->hits(shadowRay, shadowInters, shadowNormal)) {
                    double dist = shadowInters.distanceBetween(shadowRay.origin);
                    if (dist < distanceToLight) {
                        lightTransmission *= shape->getTransparency();
                        if (lightTransmission <= 0.01) break;
                    }
                }
            }
            
            // Apply light if some reaches the point
            if (lightTransmission > 0) {
                // Diffuse (Lambertian)
                double dot = closestNormal.x * lightDir.x + closestNormal.y * lightDir.y + closestNormal.z * lightDir.z;
                
                if (dot > 0) {
                    double effectiveIntensity = diffuseFactor * dot * attenuation * lightTransmission;
                    
                    r += objColor.r * effectiveIntensity;
                    g += objColor.g * effectiveIntensity;
                    b += objColor.b * effectiveIntensity;

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
                        double specFactor = specularStrength * std::pow(specDot, shininess) * attenuation * lightTransmission;
                        r += 255 * specFactor;
                        g += 255 * specFactor;
                        b += 255 * specFactor;
                    }
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

        // --- Reflections ---
        Color reflectColor = {0, 0, 0};
        if (reflectivity > 0) {
            // R = D - 2 * (D . N) * N
            double dotDN = ray.direction.x * closestNormal.x + ray.direction.y * closestNormal.y + ray.direction.z * closestNormal.z;
            maths::Vector3D reflectDir;
            reflectDir.x = ray.direction.x - 2.0 * dotDN * closestNormal.x;
            reflectDir.y = ray.direction.y - 2.0 * dotDN * closestNormal.y;
            reflectDir.z = ray.direction.z - 2.0 * dotDN * closestNormal.z;

            Raytracer::Ray reflectRay(
                maths::Point3D(closestInters.x + closestNormal.x * 0.001, 
                               closestInters.y + closestNormal.y * 0.001, 
                               closestInters.z + closestNormal.z * 0.001),
                reflectDir
            );

            reflectColor = getColor(reflectRay, depth + 1);
            pixelColor.r = pixelColor.r * (1.0 - reflectivity) + reflectColor.r * reflectivity;
            pixelColor.g = pixelColor.g * (1.0 - reflectivity) + reflectColor.g * reflectivity;
            pixelColor.b = pixelColor.b * (1.0 - reflectivity) + reflectColor.b * reflectivity;
        }

        // --- Refractions ---
        double transparency = closestShape->getTransparency();
        if (transparency > 0) {
            double n1 = 1.0; // Air
            double n2 = closestShape->getRefractiveIndex();
            
            double dotDN = ray.direction.x * closestNormal.x + ray.direction.y * closestNormal.y + ray.direction.z * closestNormal.z;
            maths::Vector3D normal = closestNormal;

            if (dotDN > 0) {
                // Ray exiting the object
                std::swap(n1, n2);
                normal.x = -normal.x; normal.y = -normal.y; normal.z = -normal.z;
            } else {
                // Ray entering the object
                dotDN = -dotDN;
            }

            double ratio = n1 / n2;
            double k = 1.0 - ratio * ratio * (1.0 - dotDN * dotDN);

            if (k >= 0) {
                // Refraction ray direction
                maths::Vector3D refractDir;
                refractDir.x = ratio * ray.direction.x + (ratio * dotDN - std::sqrt(k)) * normal.x;
                refractDir.y = ratio * ray.direction.y + (ratio * dotDN - std::sqrt(k)) * normal.y;
                refractDir.z = ratio * ray.direction.z + (ratio * dotDN - std::sqrt(k)) * normal.z;

                Raytracer::Ray refractRay(
                    maths::Point3D(closestInters.x - normal.x * 0.001, 
                                   closestInters.y - normal.y * 0.001, 
                                   closestInters.z - normal.z * 0.001),
                    refractDir
                );

                // Schlick's approximation for Fresnel
                double r0 = (n1 - n2) / (n1 + n2);
                r0 *= r0;
                double fresnel = r0 + (1.0 - r0) * std::pow(1.0 - dotDN, 5);

                Color refractColor = getColor(refractRay, depth + 1);
                
                // Blend: Transparency modulates how much of the "refracted path" we see
                pixelColor.r = pixelColor.r * (1.0 - transparency) + 
                               (reflectColor.r * fresnel + refractColor.r * (1.0 - fresnel)) * transparency;
                pixelColor.g = pixelColor.g * (1.0 - transparency) + 
                               (reflectColor.g * fresnel + refractColor.g * (1.0 - fresnel)) * transparency;
                pixelColor.b = pixelColor.b * (1.0 - transparency) + 
                               (reflectColor.b * fresnel + refractColor.b * (1.0 - fresnel)) * transparency;
            } else {
                // Total Internal Reflection
                pixelColor.r = pixelColor.r * (1.0 - transparency) + reflectColor.r * transparency;
                pixelColor.g = pixelColor.g * (1.0 - transparency) + reflectColor.g * transparency;
                pixelColor.b = pixelColor.b * (1.0 - transparency) + reflectColor.b * transparency;
            }
        }
    }

    return pixelColor;
}

