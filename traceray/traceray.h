#ifndef TRACERAY_H
#define TRACERAY_H

#include "../Vector3d/Vector3d.h"

class Shape;
class Light;

Vector3d trace_ray(Vector3d &p_0, Vector3d &dr, long double t_min, long double t_max,
                   vector<Shape *> &shapes, Vector3d &bgcolor,
                   std::vector<Light *> &lights, int x, int y);

Vector3d calculate_light_intensity(std::vector<Light *> &lights, Vector3d &n,
                                   Vector3d &v, Vector3d &pi,
                                   std::vector<Shape *> &shapes, Shape &obj,
                                   int x, int y);

bool light_being_blocked(Shape &cls_shape, vector<Shape *> &shapes,
                         Vector3d &p_i, Light &light, Vector3d &lr);

#endif