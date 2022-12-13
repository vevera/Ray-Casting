#include "scene.h"

#include <SDL2/SDL.h>

#include <algorithm>
#include <chrono>
#include <iostream>

#include "../traceray/traceray.h"
Scene::Scene(std::vector<Shape *> shapes, Canvas canvas,
             std::vector<Light *> lights, gMatrix wc)
    : shapes_(shapes), canvas_(canvas), lights_(lights), projection(Projection::PERSPECTIVE) {
    std::for_each(begin(shapes_), end(shapes_),
                  [&](Shape *shape) { *shape *wc; });

    std::for_each(begin(lights_), end(lights_),
                  [&](Light *lightp) { *lightp *wc; });
};

void Scene::take_a_picture(Vector3d camera, ViewPort vp, Vector3d bgColor) {
    long double dx = vp.width / (long double) canvas_.n_cols();
    long double dy = vp.height / (long double) canvas_.n_rows();

    long double yj;
    long double xj;

    auto start = std::chrono::steady_clock::now(); 

    int rows = canvas_.n_rows();
    int cols = canvas_.n_cols();

    Vector3d dr;
    Vector3d p0;

    canvas_.reset_count();

    for (int l = 0; l < rows; l++) {
        yj = (vp.height / 2) - (dy / 2) - (l * dy);
        for (int c = 0; c < cols; c++) {
            xj = (-vp.width / 2.0) + (dx / 2.0) + (c * dx);

            dr = projection == Projection::PERSPECTIVE? Vector3d(xj, yj, vp.z) - camera : Vector3d(0,0,-1);

            p0 = projection == Projection::PERSPECTIVE? camera : Vector3d(xj, yj, vp.z);

            Vector3d cor = trace_ray(p0, dr, vp.z, INFINITY, shapes_,
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

void Scene::set_projection(Projection projection_){
    projection = projection_;
}

Shape *Scene::picking(Vector3d &camera, long double x, long double y, long double t_min, Vector3d **clicked_point) {

    long double closest_t = INFINITY;
    long double t;
    Shape *closest_shape = nullptr;

    std::cout << "TYPE: " << (projection == Projection::PERSPECTIVE) << std::endl;
    Vector3d p0 = projection == Projection::PERSPECTIVE ? camera : Vector3d(x, y, -t_min);
    Vector3d direction = projection == Projection::PERSPECTIVE ? 
                                        (Vector3d(x, y, -t_min)).normalize() : 
                                        Vector3d(0.0, 0.0, -1.0);

    std::for_each(begin(shapes_), end(shapes_), [&](Shape *shape) {
        /****/

        
        t = shape->intersect(p0, direction);
        std::cout << "VALOR Ts: " << t << " " << t_min << std::endl;
        if ((t > 0.0) && (t >= t_min) && (t < closest_t)) {
            closest_t = t;
            closest_shape = shape;
        }
        /****/
    });

    *(*clicked_point) = p0 + (direction * closest_t);

    return closest_shape;
}

void Scene::update_world_camera(gMatrix old_cw, gMatrix new_wc){

    std::for_each(begin(shapes_), end(shapes_),
                  [&](Shape *shape) { *shape *old_cw; *shape *new_wc;});

    std::for_each(begin(lights_), end(lights_),
                  [&](Light *lightp) { *lightp *old_cw; *lightp *new_wc;});

};
