#include "cylinder.h"

Cylinder::Cylinder(Vector3d color,
             Reflexivity reflexivity,
             Vector3d p_pi,
             double radius) : Shape(color, reflexivity), p_pi_(p_pi), radius_(radius){};

double Cylinder::intersect(Vector3d p_0, Vector3d dr)
{
    double t1, t2;

    Vector3d w = p_0 - p_pi_;

    // a = dr_transposta * M * dr
    double a = dr.dot(dr);

    // b = 2 * w_transposta * M * dr
    double b = dr.dot(dr);

    // c = w_transposta * M * w - Rc2
    double c = dr.dot(dr);

    double delta = pow(b, 2) - 4 * a * c;

    if (delta < 0)
    {
        return INFINITY;
    }

    t1 = (-b + sqrt(delta)) / (2 * a);

    t2 = (-b - sqrt(delta)) / (2 * a);

    return std::min(t1, t2);

    // FALTA FAZER OS TESTES DE INTERSECÇÂO, 3 testes

};

Vector3d Cylinder::normal(Vector3d p_i)
{
    
    return p_i;
};