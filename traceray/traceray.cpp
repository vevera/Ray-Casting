#include "traceray.h"
#include <vector>
#include "../shapes/shape.h"
#include "../scene/scene.h"
#include "../light/light.h"
#include <algorithm>
#include <iostream>
#include <algorithm>
using std::vector;

Vector3d trace_ray(Vector3d p_0, Vector3d dr,
                   double t_min, double t_max,
                   vector<Shape *> &shapes, Vector3d bgcolor,
                   std::vector<Light *> &lights, int x, int y)
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
    //  Calculo do ponto de intersecção
    Vector3d p_i = p_0 + (dr * closest_t); // dr = (D - O)

    // Vetores unitários usados no modelo
    Vector3d normal, v;

    normal = closest_shape->normal(p_i);
    // lr = *light.get_l(p_i);
    //  lr = *light.position - p_i;
    // lr = lr.normalize();
    v = dr * (-1);
    v = v.normalize();
    // r = ((normal * (lr.dot(normal))) * 2) - lr;

    // Calculo da iluminação/reflexibilidade dos objetos

    // bool light_blocked = light_being_blocked(*closest_shape, shapes, p_i, light, lr);

    color = calculate_light_intensity(lights, normal, v, p_i, shapes, *closest_shape, p_i.x_, p_i.z_);

    return color;
}

Vector3d calculate_light_intensity(std::vector<Light *> &lights,
                                   Vector3d &n,
                                   Vector3d &v,
                                   Vector3d &pi,
                                   std::vector<Shape *> &shapes,
                                   Shape &obj,
                                   int x,
                                   int y)
{

    Vector3d *l, r;

    Vector3d *kd = obj.kd(x, y);
    Vector3d *ke = obj.ke(x, y);
    Vector3d *ka = obj.ka(x, y);
    double m = obj.m();
    Reflexivity reflex = Reflexivity(kd, ke, ka, m);

    Vector3d i_eye = Vector3d(0, 0, 0);

    std::for_each(begin(lights), end(lights), [&](Light *light)
                  {
                     
//light->get_l(pi)
                      l = light->get_l(pi);
                    //   *l = l->normalize();
                    //   //std::cout << l->toStr() << std::endl;
                      r = ((n * (l->dot(n))) * 2) - *l;

                      if (!light_being_blocked(obj, shapes, pi, *light, *l))
                      {
                          Vector3d i_l = *light->get_contribution(reflex, *l, n, v, r);

                          i_eye = i_eye + i_l;

                          double max = std::max({i_eye.x_, i_eye.y_, i_eye.z_});
                          i_eye = max > 1.0 ? i_eye / max : i_eye;
                      } });
    return i_eye;
    double max = std::max({i_eye.x_, i_eye.y_, i_eye.z_});

    return max > 1.0 ? i_eye / max : i_eye;

    // Vector3d *kd = obj.kd(x, y);
    // Vector3d *ke = obj.ke(x, y);
    // Vector3d *ka = obj.ka(x, y);
    // double m = obj.m();

    // Reflexivity reflex = Reflexivity(kd, ke, ka, m);

    // if (blocked)
    // {
    //     Vector3d i_a = *ambient_l.get_contribution(reflex, l, n, v, r);

    //     return i_a;
    // }

    // // diffuse reflection
    // // Vector3d i_d = ((*light.get_intensity() * (*kd)) * std::max(l.dot(n), 0.0));
    // // specular reflection
    // // Vector3d i_e = ((*light.get_intensity() * (*ke)) * std::max(pow(v.dot(r), m), 0.0));
    // Vector3d i_l = *light.get_contribution(reflex, l, n, v, r);
    // Vector3d i_a = *ambient_l.get_contribution(reflex, l, n, v, r);

    // Vector3d i_eye = i_l + i_a;

    // // std::cout << i_eye.toStr() << std::endl;

    // double max = std::max({i_eye.x_, i_eye.y_, i_eye.z_});

    // return max > 1.0 ? i_eye / max : i_eye;
}

bool light_being_blocked(Shape &cls_shape, vector<Shape *> &shapes,
                         Vector3d &p_i, Light &light,
                         Vector3d &lr)
{

    for (auto shape : shapes)
    {
        double s = shape->intersect(p_i, lr);
        double len_pi_to_light = light.get_distance_from_p(p_i);
        if (s > 0.0001 && s < len_pi_to_light)
        {
            return true;
        }
    }

    return false;
}