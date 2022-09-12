#ifndef CONE_H
#define CONE_H

#include "../shape.h"

class Cone : public Shape
{
public:
    Cone(Vector3d color, Reflexivity reflexivity, Vector3d p_pi, double radius);

    double intersect(Vector3d p_0, Vector3d dr);
    Vector3d normal(Vector3d p_i);

private:
    Vector3d p_pi_;
    double radius_;
};

#endif