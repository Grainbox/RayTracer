/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** light
*/

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

    #include <iostream>

    class Light {
        public:
            Light() {};
            ~Light() {};
            int posX;
            int posY;
            int posZ;
            float ambient;
            float diffuse;
            std::string type;
        private:
        protected:
    };

#endif /* !LIGHT_HPP_ */
