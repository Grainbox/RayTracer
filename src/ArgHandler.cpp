/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-mathieu.rio
** File description:
** ArgHandler
*/

#include "ArgHandler.hpp"

ArgHandler::ArgHandler(int argc, char **argv)
{
    this->argc = argc;

    for (int i = 0; i < argc; i++) {
        std::string str(argv[i]);
        this->argv.push_back(str);
    }
    isValidArg();
}

ArgHandler::~ArgHandler()
{
}

void ArgHandler::displayHelp()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "    SCENE_FILE: scene configuration" << std::endl;
    std::exit(0);
}

void ArgHandler::isValidArg()
{
    if (argc != 2)
        throw (InvalidArg("Invalid argument, --help to show usage."));
    if (argv[1] == "--help")
        this->displayHelp();
    if (std::filesystem::exists(argv[1])) {
        std::ifstream file(argv[1]);
        if (!file.is_open()) {
            throw (InvalidFile("Cannot open configuration file."));
        } else {
            file.close();
        }
    } else
        throw (InvalidFile("Configuration file do not exists."));
}
