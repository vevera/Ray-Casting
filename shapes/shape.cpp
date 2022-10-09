#include "shape.h"

Shape::Shape(Reflexivity reflexivity, std::string texture_path)
    : reflexivity_(reflexivity), texture_path_(texture_path){};

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