/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Parser.cpp
*/

#include <config/Parser.hpp>
#include <Raytracer.hpp>

Raytracer::Parser::ConfigParser::ConfigParser(const std::string &path) : _path(path) {
    this->parse(path);
}

void Raytracer::Parser::ConfigParser::setSceneLights(const libconfig::Setting &lights)
{
    float ambient = lights["ambient"];
    float diffuse = lights["diffuse"];

    this->_scene.setAmbientLight(ambient);
    this->_scene.setDiffuseLight(diffuse);

    if (lights.exists("point")) {
        const libconfig::Setting &pointLights = lights["point"];
        for (const auto &pointLight : pointLights) {
            maths::Point3D position(
                pointLight["position"]["x"],
                pointLight["position"]["y"],
                pointLight["position"]["z"]
            );
            this->_scene.addLight(std::make_shared<PointLight>(position));
        }
    }

    if (lights.exists("directional")) {
        const libconfig::Setting &directionalLights = lights["directional"];
        for (const auto &directionalLight : directionalLights) {
            maths::Point3D position(
                directionalLight["position"]["x"],
                directionalLight["position"]["y"],
                directionalLight["position"]["z"]);
            maths::Vector3D direction(
                directionalLight["direction"]["x"],
                directionalLight["direction"]["y"],
                directionalLight["direction"]["z"]
            );
            this->_scene.addLight(std::make_shared<DirectionalLight>(position, direction));
        }
    }

    // DUMP LIGHTS (DEBUG)
    // You need to cast DirectionalLight before PointLight because PointLight is a child of DirectionalLight
    std::cout << "\nLights:" << std::endl;
    for (const auto &light : this->_scene.getLights()) {
         if (std::dynamic_pointer_cast<DirectionalLight>(light)) {
            std::cout << "DirectionalLight" << std::endl;
            maths::Vector3D direction = std::dynamic_pointer_cast<DirectionalLight>(light)->getDirection();
            std::cout << "\t--> Direction: " << direction.x << ", " << direction.y << ", " << direction.z << std::endl;
            maths::Point3D position = std::dynamic_pointer_cast<DirectionalLight>(light)->getOrigin();
            std::cout << "\t--> Position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
        } else if (std::dynamic_pointer_cast<PointLight>(light)) {
            std::cout << "PointLight:" << std::endl;
            maths::Point3D position = std::dynamic_pointer_cast<PointLight>(light)->getOrigin();
            std::cout << "\t--> Position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
        }
    }
}


void Raytracer::Parser::ConfigParser::setScenePrimitives(const libconfig::Setting &primitives)
{
  for (const auto &primitiveGroup : primitives) {
    std::string type = primitiveGroup.getName();

    for (const auto &element : primitiveGroup) {
      try {
        this->_scene.addShape(_factory.createShape(type, element));
      } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
      }
    }
    std::cout << "type: " << type << std::endl;
  }
}

void Raytracer::Parser::ConfigParser::setSceneCamera(const libconfig::Setting &camera)
{
    if (!camera.exists("position"))
        throw std::runtime_error("No camera position found in config file");
    if (!camera.exists("rotation"))
        throw std::runtime_error("No camera rotation found in config file");
    if (!camera.exists("resolution"))
        throw std::runtime_error("No camera resolution found in config file");
    if (!camera.exists("fov"))
        throw std::runtime_error("No camera fov found in config file");

    libconfig::Setting &position = camera["position"];
    libconfig::Setting &rotation = camera["rotation"];
    libconfig::Setting &fov = camera["fov"];
    libconfig::Setting &resolution = camera["resolution"];

    if (!position.exists("x") || !position.exists("y") || !position.exists("z"))
        throw std::runtime_error("No camera position found in config file");
    if (!rotation.exists("x") || !rotation.exists("y") || !rotation.exists("z"))
        throw std::runtime_error("No camera rotation found in config file");
    if (!resolution.exists("width") || !resolution.exists("height"))
        throw std::runtime_error("No camera resolution found in config file");

    this->_scene.setCamera(Camera(
        maths::Point3D(position["x"], position["y"], position["z"]),
        maths::Vector3D(position["x"], position["y"], position["z"]),
        float(fov),
        resolution["width"],
        resolution["height"]));
}

void Raytracer::Parser::ConfigParser::setScene(const libconfig::Setting &root)
{
    if (!root.exists("scene"))
        throw std::runtime_error("No scene found in config file");
    if (!root["scene"].exists("camera"))
        throw std::runtime_error("No camera found in config file");
    if (!root["scene"].exists("primitives"))
        throw std::runtime_error("No primitives found in config file");
    if (!root["scene"].exists("lights"))
        throw std::runtime_error("No lights found in config file");

    setSceneCamera(root["scene"]["camera"]);
    setScenePrimitives(root["scene"]["primitives"]);
    setSceneLights(root["scene"]["lights"]);

    if (root["scene"].exists("samples"))
        this->_scene.setSamples(root["scene"]["samples"]);
}

void Raytracer::Parser::ConfigParser::parse(const std::string &path)
{
    _path = path;

    try {
        this->_config.readFile(path.c_str());
        this->_config.setAutoConvert(true);
        setScene(this->_config.getRoot());
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        std::cerr << fioex.what() << std::endl;
        exit(1);
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        exit(1);
    }
}

libconfig::Config &Raytracer::Parser::ConfigParser::getConfig(void)
{
    return this->_config;
}

libconfig::Setting &Raytracer::Parser::ConfigParser::getRoot(void)
{
    if (_path == "")
        throw std::runtime_error("No config file path provided");
    return this->_config.getRoot();
}