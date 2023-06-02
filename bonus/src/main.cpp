/*
** EPITECH PROJECT, 2023
** Projet
** File description:
** main
*/

#include "my.hpp"

int main (int argc, char **argv)
{
    if (argc < 2)
        return 84;
    if ((std::string) (argv[1]) == "--help") {
        std::cout << "./Bonus [Path to Makefile] [Path to cfg] [Path to ppm]" << std::endl;
        return 0;
    }
    if (argc < 4)
        return 84;
    Window win(argv);
    win.display();
    return 0;
}
