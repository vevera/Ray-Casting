#include "traceray.h"
#include <vector>
#include "../shapes/shape.h"
#include "../scene/scene.h"
#include <algorithm>
#include <iostream>
#include <algorithm>
using std::vector;

Vector3d trace_ray(Vector3d p_0, Vector3d dr,
                   double t_min, double t_max,
                   vector<Shape *> &shapes, Vector3d bgcolor,
                   Light light, Light ambient_light)
{
    Vector3d color;

    // std::cout << light.intensity->toStr() << std::endl;
    // std::cout << ambient_light.intensity->toStr() << std::endl;

    double closest_t = INFINITY;
    Shape *closest_shape = nullptr;
    double t = 0;

    // std::cout << "antes for each" << std::endl;
    std::for_each(shapes.begin(), shapes.end(), [&](Shape *shape)
                  {
        //std::cout << "antes intersect" << std::endl;             
        t = shape->intersect(p_0, dr);
        //std::cout << t << "/" << std::endl;
        //std::cout << "depois intersect" << std::endl;
        if ((t > 0) && ((t>= t_min) && (t <= t_max)) && (t < closest_t))
        {
        
        closest_t = t;
        closest_shape = shape;
    } });
    // std::cout << "depois for each" << std::endl;

    if (closest_shape == nullptr)
    {
        // std::cout << bgcolor.x_ << std::endl;
        return bgcolor;
    }
    // std::cout << "linha 37" << std::endl;
    //  Calculo do ponto de intersecção com a esfera
    Vector3d p_i = p_0 + (dr * closest_t); // dr = (D - O)

    // Vetores unitários usados no modelo
    Vector3d normal, lr, v, r;

    normal = closest_shape->normal(p_i);
    // std::cout << "linha 45" << std::endl;
    lr = *light.position - p_i;
    lr = lr.normalize();
    v = dr * (-1);
    v = dr.normalize();
    r = ((normal * (lr.dot(normal))) * 2) - lr;
    // std::cout << "linha 50" << std::endl;

    // Calculo da iluminação/reflexibilidade dos objetos

    bool light_blocked = light_being_blocked(*closest_shape, shapes, p_i, light, lr);

    color = calculate_light_intensity(light, normal, lr, v, r, *closest_shape, ambient_light, light_blocked);

    // std::cout << "fim trace ray" << std::endl;

    return color;
}

Vector3d calculate_light_intensity(Light light, Vector3d &n,
                                   Vector3d &l, Vector3d &v,
                                   Vector3d &r, Shape &obj,
                                   Light &ambient_l, bool blocked)
{

    Vector3d *kd = obj.kd();
    Vector3d *ke = obj.ke();
    Vector3d *ka = obj.ka();
    double m = obj.m();
    Vector3d *color = obj.color();

    if (blocked)
    {
        Vector3d i_a = *ambient_l.intensity * (*ka);

        Vector3d rgb = *obj.color() * i_a;

        return rgb;
    }

    // diffuse reflection
    Vector3d i_d = ((*light.intensity * (*kd)) * std::max(l.dot(n), 0.0));
    // specular reflection
    Vector3d i_e = ((*light.intensity * (*ke)) * pow(v.dot(r), m));

    Vector3d i_a = *ambient_l.intensity * (*ka);

    Vector3d i_eye = i_d + i_e + i_a;

    Vector3d rgb = *obj.color() * i_eye;

    Vector3d rgb_f(std::min(rgb.x_, 255.0), std::min(rgb.y_, 255.0), std::min(rgb.z_, 255.0));

    return rgb_f;
}

bool light_being_blocked(Shape &cls_shape, vector<Shape *> &shapes,
                         Vector3d &p_i, Light &light,
                         Vector3d &lr)
{
    bool is_blocked = false;
    std::for_each(shapes.begin(), shapes.end(), [&](Shape *shape)
                  {
        if (shape != &cls_shape)
        {
        
            double s = shape->intersect(p_i, lr);
            Vector3d pi_to_light = *light.position - p_i;
            double len_pi_to_light = pi_to_light.length();
            if (s > 0 && s < len_pi_to_light) {
                is_blocked = true;
            }
        } });
    return is_blocked;
}