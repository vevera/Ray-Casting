#ifndef PLANE_H
#define PLANE_H

#include "../shape.h"

class Plane : public Shape
{
public:
    Plane(Vector3d color, Reflexivity reflexivity, Vector3d p_pi, Vector3d n);

    double intersect(Vector3d p_0, Vector3d dr);
    Vector3d normal(Vector3d p_i);

private:
    Vector3d p_pi_;
    Vector3d n_;
};

#endif