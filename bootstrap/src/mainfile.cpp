/*
** EPITECH PROJECT, 2023
** repositories
** File description:
** mainfile
*/

#include "Raytracer.hpp"

// int main(void)
// {
//     maths::Point3D center(1, 2, 3);
//     maths::Point3D origin(0, 0, 0);
//     maths::Vector3D vector(1, 1, 1);
//     RayTracer::Sphere sphere(center, 2);
//     RayTracer::Ray ray(origin, vector);
//     if (sphere.hits(ray))
//         printf("HITS\n");
//     return 0;
// }

int main()
{
    RayTracer::Camera cam;
    RayTracer::Sphere s(maths::Point3D(0, 0, -1), 0.5);
    for (double x = 0; x < 2000; x++) {
        for (double y = 0; y < 2000; y++) {
            RayTracer::Ray r = cam.ray(x, y);
            if (s.hits(r)) {
                printf("red pixel !\n");
            } else {
                // printf("green\n");
            }
        }
    }
    
    std::ofstream myfile;
    myfile.open ("test.ppm");

    std::string final_content;
    int height = 200;
    int width = 200;
    int max_pixel_val = 255;

    final_content +=
        "P3 " + std::to_string(width) + " " +std::to_string(height) +
        " " + std::to_string(max_pixel_val) + "\n"; // Header

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            final_content += "50 "; // R
            final_content += "168 "; // G
            final_content += "82 "; // B
        }
    }

    myfile << final_content;
    myfile.close();
}