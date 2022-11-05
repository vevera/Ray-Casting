#include "traceray.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "../light/light.h"
#include "../scene/scene.h"
#include "../shapes/shape.h"
using std::vector;

Vector4d trace_ray(Vector4d &p_0, Vector4d &dr, double t_min, double t_max,
                   vector<Shape *> &shapes, Vector4d &bgcolor,
                   std::vector<Light *> &lights, int x, int y) {
    Vector4d color;

    double closest_t = INFINITY;
    Shape *closest_shape = nullptr;
    double t = 0;
    // dr.set(3, 0);
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
    Vector4d p_i = p_0 + (dr * closest_t);   // dr = (D - O)

    // Vetores unitários usados no modelo
    Vector4d normal, v;

    normal = closest_shape->normal(p_i);
    // lr = *light.get_l(p_i);
    //  lr = *light.position - p_i;
    // lr = lr.normalize();
    v = dr * (-1);
    v = v.normalized();
    // r = ((normal * (lr.dot(normal))) * 2) - lr;

    // Calculo da iluminação/reflexibilidade dos objetos

    // bool light_blocked = light_being_blocked(*closest_shape, shapes, p_i,
    // light, lr);
    // color = *closest_shape->kd(p_i.x_, p_i.z_);
    color = calculate_light_intensity(lights, normal, v, p_i, shapes,
                                      *closest_shape, p_i(0), p_i(2));

    return color;
}

Vector4d calculate_light_intensity(std::vector<Light *> &lights, Vector4d &n,
                                   Vector4d &v, Vector4d &pi,
                                   std::vector<Shape *> &shapes, Shape &obj,
                                   int x, int y) {
    Vector4d *l, r;

    Vector4d *kd = obj.kd(x, y);
    Vector4d *ke = obj.ke(x, y);
    Vector4d *ka = obj.ka(x, y);
    Vector4d i_eye = Vector4d(0, 0, 0, 0);
    Vector4d i_l;
    double m = obj.m();
    double max;
    Reflexivity reflex = Reflexivity(kd, ke, ka, m);

    std::for_each(begin(lights), end(lights), [&](Light *light) {
        l = light->get_l(pi);

        r = ((n * (l->dot(n))) * 2) - *l;

        if (!light_being_blocked(obj, shapes, pi, *light, *l)) {
            i_l = *light->get_contribution(reflex, *l, n, v, r);

            i_eye = i_eye + i_l;
        }
    });
    max = std::max({i_eye(0), i_eye(1), i_eye(2)});
    i_eye = max > 1.0 ? i_eye / max : i_eye;
    return i_eye;
}

bool light_being_blocked(Shape &cls_shape, vector<Shape *> &shapes,
                         Vector4d &p_i, Light &light, Vector4d &lr) {
    double s, len_pi_to_light;
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