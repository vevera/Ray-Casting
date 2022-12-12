#include "traceray.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "../light/light.h"
#include "../scene/scene.h"
#include "../shapes/shape.h"
using std::vector;

Vector3d trace_ray(Vector3d &p_0, Vector3d &dr, long double t_min, long double t_max,
                   vector<Shape *> &shapes, Vector3d &bgcolor,
                   std::vector<Light *> &lights, int x, int y) {
    Vector3d color;

    long double closest_t = INFINITY;
    Shape *closest_shape = nullptr;
    long double t = 0;
    dr.set(3, 0);
    std::for_each(begin(shapes), end(shapes), [&](Shape *shape) {
        t = shape->intersect(p_0, dr);
        if ((t > 0) && ((t >= t_min) && (t <= t_max)) && (t < closest_t)) {
            closest_t = t;
            closest_shape = shape;
        }
    });

    if (closest_shape == nullptr)
        return bgcolor;
    //  Calculo do ponto de intersecção
    Vector3d p_i = p_0 + (dr * closest_t);   // dr = (D - O)

    // Vetores unitários usados no modelo
    Vector3d normal, v;

    normal = closest_shape->normal(p_i);
    
    v = dr * (-1);
    v = v.normalize();
    
    color = calculate_light_intensity(lights, normal, v, p_i, shapes,
                                      *closest_shape, p_i.x_, p_i.z_);

    return color;
}

Vector3d calculate_light_intensity(std::vector<Light *> &lights, Vector3d &n,
                                   Vector3d &v, Vector3d &pi,
                                   std::vector<Shape *> &shapes, Shape &obj,
                                   int x, int y) {
    Vector3d l, r;

    Vector3d kd = obj.kd(x, y);
    Vector3d ke = obj.ke(x, y);
    Vector3d ka = obj.ka(x, y);
    Vector3d i_eye = Vector3d(0, 0, 0);
    //Vector3d i_l;
    long double m = obj.m();
    long double max;
    Reflexivity reflex = Reflexivity(kd, ke, ka, m);

    std::for_each(begin(lights), end(lights), [&](Light *light) {
        l = light->get_l(pi);

        r = ((n * (l.dot(n))) * 2) - l;

        if (!light_being_blocked(obj, shapes, pi, *light, l)) {
            //i_l = light->get_contribution(reflex, l, n, v, r);

            i_eye = i_eye + light->get_contribution(reflex, l, n, v, r);
        }
    });
    max = std::max({i_eye.x_, i_eye.y_, i_eye.z_});
    //i_eye = max > 1.0 ? i_eye / max : i_eye;
    return max > 1.0 ? i_eye / max : i_eye;
}

bool light_being_blocked(Shape &cls_shape, vector<Shape *> &shapes,
                         Vector3d &p_i, Light &light, Vector3d &lr) {

    // if (cls_shape.ignore_shape_) {
    //     return false;
    // }

    long double s, len_pi_to_light;
    Shape *shape;
    for (int shape_ind = 0; shape_ind < shapes.size(); shape_ind++) {
        shape = shapes.at(shape_ind);
        s = shape->intersect(p_i, lr);
        len_pi_to_light = light.get_distance_from_p(p_i);

        if (s > 0.0001 && s < len_pi_to_light) {
            return true;
        }
    }

    return false;
}