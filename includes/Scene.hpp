/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Parser.hpp
*/

#pragma once

#include <vector>
#include <memory>
#include "Raytracer.hpp"
#include <shapes/IShape.hpp>

namespace Raytracer
{
    class Scene {
        public:
            Scene() = default;
            ~Scene() = default;

            void addShape(const std::shared_ptr<IShape> shape);
            void addLight(std::shared_ptr<ALight> light);
            void setCamera(const Camera &camera);
            void setAmbientLight(float ambient) { this->ambient = ambient;}
            void setDiffuseLight(float diffuse) { this->diffuse = diffuse;}
            void setSamples(int samples) { this->samples = samples; }
            std::vector<std::shared_ptr<IShape>> getShapes() const { return shapes; }
            std::vector<std::shared_ptr<ALight>> getLights() const { return lights; }
            std::string render();

        private:
            Color getColor(int x, int y);
            Color getColor(const Ray &ray, int depth);
            float ambient;
            float diffuse;
            int samples = 1;
            static const int MAX_DEPTH = 5;

            std::vector<std::shared_ptr<IShape>> shapes;
            std::vector<std::shared_ptr<ALight>> lights;
            Camera camera;
    };
}