#include "cone.h"

Cone::Cone(Vector3d color,
             Reflexivity reflexivity,
             Vector3d p_pi,
             double radius) : Shape(color, reflexivity), p_pi_(p_pi), radius_(radius){};

double Cone::intersect(Vector3d p_0, Vector3d dr)
{
    double t = 0;

    return t;
};

Vector3d Cone::normal(Vector3d p_i)
{
    return p_i;
};