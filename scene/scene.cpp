#include "scene.h"
#include "../traceray/traceray.h"
#include <iostream>
Scene::Scene(std::vector<Shape *> shapes,
             Canvas canvas,
             Light &light,
             Light &ambient_light) : shapes_(shapes),
                                     canvas_(canvas),
                                     light_(&light),
                                     ambient_light_(&ambient_light){};

void Scene::take_a_picture(Vector3d camera, ViewPort vp, Vector3d bgColor)
{
    double dx = vp.width / (double)canvas_.n_cols();
    double dy = vp.height / (double)canvas_.n_rows();

    double yj;
    double xj;

    for (int l = 0; l < canvas_.n_rows(); l++)
    {
        yj = (vp.height / 2) - (dy / 2) - (l * dy);
        for (int c = 0; c < canvas_.n_cols(); c++)
        {
            xj = (-vp.width / 2.0) + (dx / 2.0) + (c * dx);

            Vector3d dr = Vector3d(xj, yj, vp.z) - camera;

            Vector3d cor = trace_ray(camera, dr,
                                     vp.z, INFINITY,
                                     shapes_, bgColor,
                                     *light_, *ambient_light_, c, l);

            canvas_.add_pixel(cor);
        }
    }
}