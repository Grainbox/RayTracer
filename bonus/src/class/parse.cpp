/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** parse
*/

#include "my.hpp"

Parse::Parse (std::string path)
{
    try {
        cfg.readFile(path);
        init_camera();
        init_light(); // erreur
        init_primitive(); // erreur
    } catch(const libconfig::FileIOException &fioex) {
        std::cerr << "Erreur lors de la lecture du fichier." << std::endl;
    } catch(const libconfig::ParseException &pex) {
        std::cerr << "Erreur de syntaxe dans le fichier de configuration à la ligne "
              << pex.getLine() << ": " << pex.getError() << std::endl;
    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "La clé spécifiée est introuvable dans le fichier de configuration." << std::endl;
    }
}

Parse::~Parse ()
{
}

void Parse::init_camera()
{
    cfg.lookupValue("scene.camera.resolution.width", _camera.width);
    cfg.lookupValue("scene.camera.resolution.height", _camera.height);

    // Position
    cfg.lookupValue("scene.camera.position.x", _camera.posX);
    cfg.lookupValue("scene.camera.position.y", _camera.posY);
    cfg.lookupValue("scene.camera.position.z", _camera.posZ);

    // Rotation
    cfg.lookupValue("scene.camera.rotation.x", _camera.rotX);
    cfg.lookupValue("scene.camera.rotation.y", _camera.rotY);
    cfg.lookupValue("scene.camera.rotation.z", _camera.rotZ);

    // Champ de vision (Field of View)
    cfg.lookupValue("scene.camera.fov", _camera.fov);
}

void Parse::init_light()
{
    const libconfig::Setting &points = cfg.lookup("scene.lights.point");
    const libconfig::Setting &light = cfg.lookup("scene.lights");
    int numPoint = points.getLength();
    for (int i = 0; i < numPoint; ++i) {
        const libconfig::Setting& point = points[i];
        Light tmpLight;
        light.lookupValue("ambient", tmpLight.ambient);
        light.lookupValue("diffuse", tmpLight.diffuse);
        point.lookupValue("position.x", tmpLight.posX);
        point.lookupValue("position.y", tmpLight.posY);
        point.lookupValue("position.z", tmpLight.posZ);
        tmpLight.type = "directional";
        lightVector.push_back(tmpLight);
    }
}

void Parse::init_primitive()
{
    // Liste des sphères
    const libconfig::Setting &spheres = cfg.lookup("scene.primitives.spheres");
    int numSpheres = spheres.getLength();

    for (int i = 0; i < numSpheres; ++i) {
        const libconfig::Setting& sphere = spheres[i];
        Primitive spherePrimitive("sphere");
        sphere.lookupValue("position.x", spherePrimitive.posX);
        sphere.lookupValue("position.y", spherePrimitive.posY);
        sphere.lookupValue("position.z", spherePrimitive.posZ);
        sphere.lookupValue("radius", spherePrimitive.radius);
        sphere.lookupValue("color.r", spherePrimitive.ColorR);
        sphere.lookupValue("color.g", spherePrimitive.ColorG);
        sphere.lookupValue("color.b", spherePrimitive.ColorB);
        primitiveVector.push_back(spherePrimitive);
    }

    // Liste des plans
    const libconfig::Setting& planes = cfg.lookup("scene.primitives.planes");
    int numPlanes = planes.getLength();

    for (int i = 0; i < numPlanes; ++i) {
        const libconfig::Setting& plane = planes[i];
        Primitive planePrimitive("plane");
        plane.lookupValue("axis", planePrimitive.axis);
        plane.lookupValue("position", planePrimitive.position);
        plane.lookupValue("color.r", planePrimitive.ColorR);
        plane.lookupValue("color.g", planePrimitive.ColorG);
        plane.lookupValue("color.b", planePrimitive.ColorB);
        primitiveVector.push_back(planePrimitive);
    }
}

void Parse::writeToFile(std::string filePath) {
    std::ofstream outputFile(filePath);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return;
    }

    // Écrire la configuration de la caméra
    outputFile << "scene:\n";
    outputFile << "{\n";
    outputFile << "  camera:\n";
    outputFile << "  {\n";
    outputFile << "    resolution: { width = " << _camera.width << "; height = " << _camera.height << "; };\n";
    outputFile << "    position: { x = " << _camera.posX << "; y = " << _camera.posY << "; z = " << _camera.posZ << "; };\n";
    outputFile << "    rotation: { x = " << _camera.rotX << "; y = " << _camera.rotY << "; z = " << _camera.rotZ << "; };\n";
    outputFile << "    fov: " << _camera.fov << ";\n";
    outputFile << "  };\n";

    // Écrire la configuration des lumières
    outputFile << "  lights:\n";
    outputFile << "  {\n";
    outputFile << "    ambient = " << lightVector.front().ambient << ";\n";
    outputFile << "    diffuse = " << lightVector.front().diffuse << ";\n";

    outputFile << "    point: (\n";
    for (const Light& light : lightVector) {
        if (light.type == "point") {
            outputFile << "      { position: { x = " << light.posX << "; y = " << light.posY << "; z = " << light.posZ << "; } }\n";
        }
    }
    outputFile << "    );\n";

    outputFile << "  };\n";

    // Écrire la configuration des primitives
    outputFile << "  primitives:\n";
    outputFile << "  {\n";

    outputFile << "    spheres: (\n";
    for (const Primitive& primitive : primitiveVector) {
        if (primitive.type == "sphere") {
            outputFile << "      {\n";
            outputFile << "        position: { x = " << primitive.posX << "; y = " << primitive.posY << "; z = " << primitive.posZ << "; };\n";
            outputFile << "        radius = " << primitive.radius << ";\n";
            outputFile << "        color: { r = " << primitive.ColorR << "; g = " << primitive.ColorG << "; b = " << primitive.ColorB << "; };\n";
            outputFile << "      }\n";
        }
    }
    outputFile << "    );\n";

    outputFile << "    planes: (\n";
    for (const Primitive& primitive : primitiveVector) {
        if (primitive.type == "plane") {
            outputFile << "      {\n";
            outputFile << "        axis = \"" << primitive.axis << "\";\n";
            outputFile << "        position = " << primitive.position << ";\n";
            outputFile << "        color: { r = " << primitive.ColorR << "; g = " << primitive.ColorG << "; b = " << primitive.ColorB << "; };\n";
            outputFile << "      }\n";
        }
    }
    outputFile << "    );\n";

    outputFile << "  };\n";

    outputFile << "};\n";

    outputFile.close();
}