#ifndef TRACERAY_H
#define TRACERAY_H

// #include "../Vector3d/Vector3d.h"

#include <Eigen/Dense>
#include <vector>
class Shape;
class Light;

using Eigen::Vector4d;
using std::vector;
Vector4d trace_ray(Vector4d &p_0, Vector4d &dr, double t_min, double t_max,
                   vector<Shape *> &shapes, Vector4d &bgcolor,
                   std::vector<Light *> &lights, int x, int y);

Vector4d calculate_light_intensity(std::vector<Light *> &lights, Vector4d &n,
                                   Vector4d &v, Vector4d &pi,
                                   std::vector<Shape *> &shapes, Shape &obj,
                                   int x, int y);

bool light_being_blocked(Shape &cls_shape, vector<Shape *> &shapes,
                         Vector4d &p_i, Light &light, Vector4d &lr);

#endif