#include "shape.h"

Shape::Shape(Vector3d color,
             Reflexivity reflexivity)
    : color_(color), reflexivity_(reflexivity){};

Vector3d *Shape::kd()
{
    return reflexivity_.kd;
};

Vector3d *Shape::ke()
{
    return reflexivity_.ke;
};

Vector3d *Shape::ka()
{
    return reflexivity_.ka;
};

double Shape::m()
{
    return reflexivity_.m;
};

Vector3d *Shape::color()
{
    return &color_;
};