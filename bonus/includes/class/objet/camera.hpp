/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

    class Camera {
        public:
            Camera() {};
            ~Camera() {};
            int width;
            int height;
            int posX;
            int posY;
            int posZ;
            int rotX;
            int rotY;
            int rotZ;
            double fov;
        private:
        protected:
    };

#endif /* !CAMERA_HPP_ */
