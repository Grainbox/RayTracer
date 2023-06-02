/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-mathieu.rio
** File description:
** ArgHandler
*/

#ifndef ARGHANDLER_HPP_
#define ARGHANDLER_HPP_

    #include <vector>
    #include <iostream>
    #include <iomanip>
    #include <filesystem>
    #include <fstream>

class InvalidArg : public std::exception {
    public:
        explicit InvalidArg(const char* message) : msg_(message) {}
        explicit InvalidArg(const std::string& message) : msg_(message) {}

        virtual const char* what() const noexcept override {
            return msg_.c_str();
        }

    private:
        std::string msg_;
};

class InvalidFile : public std::exception {
    public:
        explicit InvalidFile(const char* message) : msg_(message) {}
        explicit InvalidFile(const std::string& message) : msg_(message) {}

        virtual const char* what() const noexcept override {
            return msg_.c_str();
        }

    private:
        std::string msg_;
};

class ArgHandler {
    public:
        ArgHandler(int argc, char **argv);
        ~ArgHandler();

    protected:
    private:
        std::vector<std::string> argv;
        int argc;

        void isValidArg();
        void displayHelp();
};

#endif /* !ARGHANDLER_HPP_ */
