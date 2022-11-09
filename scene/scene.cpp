#include "scene.h"

#include <SDL2/SDL.h>

#include <algorithm>
#include <chrono>
#include <iostream>

#include "../traceray/traceray.h"
Scene::Scene(std::vector<Shape *> shapes, Canvas canvas,
             std::vector<Light *> lights, gMatrix wc)
    : shapes_(shapes), canvas_(canvas), lights_(lights) {
    std::for_each(begin(shapes_), end(shapes_),
                  [&](Shape *shape) { *shape *wc; });
};

void Scene::take_a_picture(Vector3d camera, ViewPort vp, Vector3d bgColor) {
    double dx = vp.width / (double) canvas_.n_cols();
    double dy = vp.height / (double) canvas_.n_rows();

    double yj;
    double xj;

    auto start = std::chrono::steady_clock::now();

    Vector3d dr_ort = Vector3d(0, 0, -1);

    int rows = canvas_.n_rows();
    int cols = canvas_.n_cols();

    canvas_.reset_count();
    for (int l = 0; l < rows; l++) {
        yj = (vp.height / 2) - (dy / 2) - (l * dy);
        for (int c = 0; c < cols; c++) {
            xj = (-vp.width / 2.0) + (dx / 2.0) + (c * dx);

            Vector3d dr = Vector3d(xj, yj, vp.z) - camera;

            // Vector3d point = Vector3d(xj, yj, vp.z);

            Vector3d cor = trace_ray(camera, dr, vp.z, INFINITY, shapes_,
                                     bgColor, lights_, c, l);

            canvas_.add_pixel(cor);
        }
    }
    std::cout << "Elapsed(ms)="
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::steady_clock::now() - start)
                         .count() /
                     1000.0
              << std::endl;
}

Shape *Scene::picking(Vector3d &p0, Vector3d &direction, double t_min) {
    double closest_t = INFINITY;
    double t;
    Shape *closest_shape = nullptr;

    std::for_each(begin(shapes_), end(shapes_), [&](Shape *shape) {
        /****/

        t = shape->intersect(p0, direction);
        if ((t > 0) && (t >= t_min) && (t < closest_t)) {
            closest_t = t;
            closest_shape = shape;
        }
        /****/
    });

    return closest_shape;
}
