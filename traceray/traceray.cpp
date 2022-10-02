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

    double closest_t = INFINITY;
    Shape *closest_shape = nullptr;
    double t = 0;

    std::for_each(shapes.begin(), shapes.end(), [&](Shape *shape)
                  {          
        t = shape->intersect(p_0, dr);
        if ((t > 0) && ((t>= t_min) && (t <= t_max)) && (t < closest_t))
        {
        
        closest_t = t;
        closest_shape = shape;
    } });

    if (closest_shape == nullptr)
        return bgcolor;
    //  Calculo do ponto de intersecção com a esfera
    Vector3d p_i = p_0 + (dr * closest_t); // dr = (D - O)

    // Vetores unitários usados no modelo
    Vector3d normal, lr, v, r;

    normal = closest_shape->normal(p_i);
    lr = *light.position - p_i;
    lr = lr.normalize();
    v = dr * (-1);
    v = v.normalize();
    r = ((normal * (lr.dot(normal))) * 2) - lr;

    // Calculo da iluminação/reflexibilidade dos objetos

    bool light_blocked = light_being_blocked(*closest_shape, shapes, p_i, light, lr);

    color = calculate_light_intensity(light, normal, lr, v, r, *closest_shape, ambient_light, light_blocked);

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

    if (blocked)
    {
        Vector3d i_a = *ambient_l.intensity * (*ka);

        return i_a;
    }

    // diffuse reflection
    Vector3d i_d = ((*light.intensity * (*kd)) * std::max(l.dot(n), 0.0));
    // specular reflection
    Vector3d i_e = ((*light.intensity * (*ke)) * std::max(pow(v.dot(r), m), 0.0));

    Vector3d i_a = *ambient_l.intensity * (*ka);

    Vector3d i_eye = i_d + i_e + i_a;

    //std::cout << i_eye.toStr() << std::endl;

    double max = std::max({i_eye.x_, i_eye.y_, i_eye.z_});

    return max > 1 ? i_eye / max : i_eye;
}

bool light_being_blocked(Shape &cls_shape, vector<Shape *> &shapes,
                         Vector3d &p_i, Light &light,
                         Vector3d &lr)
{
    for (auto shape : shapes)
    {
        double s = shape->intersect(p_i, lr);
        Vector3d pi_to_light = *light.position - p_i;
        double len_pi_to_light = pi_to_light.length();
        if (s > eps && s < len_pi_to_light)
        {
            return true;
        }
    }

    return false;
}