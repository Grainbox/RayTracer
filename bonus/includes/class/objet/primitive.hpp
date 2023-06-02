/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** primitive
*/

#ifndef PRIMITIVE_HPP_
#define PRIMITIVE_HPP_

    #include <iostream>

    class Primitive {
        public:
            Primitive(std::string type) : type(type) {};
            ~Primitive () {};
            int posX = 0;
            int posY = 0;
            int posZ = 0;
            float radius = 0;
            int ColorR = 0;
            int ColorG = 0;
            int ColorB = 0;
            std::string axis = "Z";
            int position = 0;
            std::string type;
        private:
        protected:
    };

#endif /* !PRIMITIVE_HPP_ */
