#include "plane.h"

Plane::Plane(Reflexivity reflexivity,
             Vector3d p_pi,
             Vector3d n) : Shape(reflexivity), p_pi_(p_pi), n_(n){};

double Plane::intersect(Vector3d p_0, Vector3d dr)
{
    double t;

    Vector3d w = p_0 - p_pi_;

    double den = dr.dot(n_);

    if (den == 0)
    {
        return INFINITY;
    }

    t = (w * -1).dot(n_) / den;

    return t;
};

Vector3d Plane::normal(Vector3d p_i)
{
    return n_;
};