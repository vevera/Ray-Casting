#ifndef SHAPE_H
#define SHAPE_H

#include "../Vector3d/Vector3d.h"
#include <memory>
#include <cmath>

struct Reflexivity
{
    Vector3d *kd = new Vector3d(1, 1, 1);
    Vector3d *ke = new Vector3d(1, 1, 1);
    Vector3d *ka = new Vector3d(1, 1, 1);
    double m = 1;
};

class Shape
{

public:
    Shape(Vector3d color, Reflexivity reflexivity);
    virtual double intersect(Vector3d p_0, Vector3d dr) = 0;
    virtual Vector3d normal(Vector3d p_i) = 0;
    Vector3d *kd();
    Vector3d *ke();
    Vector3d *ka();
    double m();
    Vector3d *color();

private:
    Vector3d color_;
    Reflexivity reflexivity_;
};

#endif