#ifndef CONE_H
#define CONE_H

#include "../shape.h"
#include "../plane/plane.h"

enum INTERSECTION_CONE_TYPE
{
    CONE_SURFACE,
    BASE_CONE_SURFACE,
};

class Cone : public Shape
{
public:
    Cone(Vector3d color, Reflexivity reflexivity,
         Vector3d base_center, Vector3d vertex,
         double radius);

    Cone(Vector3d color, Reflexivity reflexivity,
         Vector3d base_center, double height,
         Vector3d cone_direction, double radius);

    double intersect(Vector3d p_0, Vector3d dr);
    Vector3d normal(Vector3d p_i);

private:
    Plane *base_plane_;
    Vector3d base_center_;
    Vector3d vertex_;
    Vector3d cone_direction_;
    double height_;
    double radius_;
    bool in_cone_surface(Vector3d &p0, Vector3d &dr, double &t);
    bool in_base_surface(Vector3d &p0, Vector3d &dr, double &t, Vector3d &base_center_);
    INTERSECTION_CONE_TYPE type = INTERSECTION_CONE_TYPE::CONE_SURFACE;
};

#endif