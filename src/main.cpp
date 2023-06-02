/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-mathieu.rio
** File description:
** main
*/

#include "ArgHandler.hpp"
#include "Raytracer.hpp"
#include "Core.hpp"

int main(int argc, char **argv)
{
    try {
        ArgHandler arg(argc, argv);
        Raytracer::Core core(argv[1]);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
    return 0;
}
