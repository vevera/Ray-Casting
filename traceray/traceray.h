#ifndef TRACERAY_H
#define TRACERAY_H

#include "../Vector3d/Vector3d.h"

class Shape;
class Light;

Vector3d trace_ray(Vector3d p_0, Vector3d dr,
                   double t_min, double t_max,
                   vector<Shape *> &shapes, Vector3d bgcolor,
                   Light light, Light ambient_light);

Vector3d calculate_light_intensity(Light light, Vector3d &n,
                                   Vector3d &l, Vector3d &v,
                                   Vector3d &r, Shape &obj,
                                   Light &ambient_l, bool blocked);

bool light_being_blocked(Shape &cls_shape, vector<Shape *> &shapes,
                         Vector3d &p_i, Light &light,
                         Vector3d &lr);

#endif