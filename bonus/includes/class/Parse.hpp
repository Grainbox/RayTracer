/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** Parse
*/

#ifndef PARSE_HPP_
#define PARSE_HPP_

    #include "objet/camera.hpp"
    #include "objet/light.hpp"
    #include "objet/primitive.hpp"
    #include <vector>

    class Parse {
        public:
            Parse(std::string path);
            ~Parse();
            void init_camera();
            Camera get_camera() { return _camera; };
            void init_light();
            std::vector<Light> get_light() { return lightVector; };
            void init_primitive();
            std::vector<Primitive> get_primitive() { return primitiveVector; };
            void writeToFile(std::string filePath);
        protected:
        private:
            libconfig::Config cfg;
            Camera _camera;
            std::vector<Primitive> primitiveVector;
            std::vector<Light> lightVector;
    };

#endif /* !PARSE_HPP_ */
