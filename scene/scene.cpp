#include "scene.h"
#include "../traceray/traceray.h"
#include <iostream>
Scene::Scene(std::vector<Shape *> shapes,
             Canvas canvas,
             Light light,
             Light ambient_light) : shapes_(shapes),
                                    canvas_(canvas),
                                    light_(light),
                                    ambient_light_(ambient_light){};

void Scene::take_a_picture(Vector3d camera, ViewPort vp, Vector3d bgColor)
{
    std::cout << "take a pic" << std::endl;
    double dx = vp.width / canvas_.n_cols();
    double dy = vp.height / canvas_.n_rows();
    vector<Vector3d> row;

    for (int l = 0; l < canvas_.n_rows(); l++)
    {
        // std::cout << "ENTROU NO FOR ";
        // std::cout << canvas_.n_rows();
        double yj = (vp.height / 2) - (dy / 2) - (l * dy);
        for (int c = 0; c < canvas_.n_cols(); c++)
        {
            // std::cout << "ENTROU NO FOR C";
            // std::cout << canvas_.n_cols();
            double xj = (-vp.width / 2) + (dx / 2) + (c * dx);
            Vector3d dr = Vector3d(xj, yj, vp.z) - camera;
            // std::cout << "TRACE RAY";
            Vector3d cor = trace_ray(camera, dr,
                                     vp.z, INFINITY,
                                     shapes_, bgColor,
                                     light_, ambient_light_);
            // std::cout << "TRACE RAY SAIDA";
            row.push_back(cor);
            // std::cout << cor.toStr() << " ";
        }
        // std::cout << std::endl;
        canvas_.add_row(row);
        // row.clear();
    }
    // canvas_.print_vector();
}