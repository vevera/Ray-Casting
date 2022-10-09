#include "sphere.h"

Sphere::Sphere(Reflexivity reflexivity,
               Vector3d center,
               double radius,
               std::string texture_path) : Shape(reflexivity, texture_path),
                                           center_(center),
                                           radius_(radius){};

double Sphere::intersect(Vector3d p_0, Vector3d dr)
{
    double t1 = 0, t2 = 0, a = 0, b = 0, c = 0, delta = 0;

    Vector3d w = p_0 - center_;

    a = dr.dot(dr);
    b = 2 * (w.dot(dr));
    c = w.dot(w) - pow(radius_, 2);

    delta = pow(b, 2) - 4 * a * c;

    if (delta < 0)
    {
        return INFINITY;
    }

    t1 = (-b + sqrt(delta)) / (2 * a);

    t2 = (-b - sqrt(delta)) / (2 * a);

    return std::min(t1, t2);
}

Vector3d Sphere::normal(Vector3d p_i)
{
    return (p_i - center_) / radius_;
}