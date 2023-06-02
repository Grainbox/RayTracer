/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-mathieu.rio
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

    #include <config/Parser.hpp>
    #include "Raytracer.hpp"
    #include <iostream>

namespace Raytracer
{
    class Core {
        public:
            Core(std::string config_path);
            ~Core();

        protected:
        private:
            Parser::ConfigParser _config;
    };
}
#endif /* !CORE_HPP_ */
