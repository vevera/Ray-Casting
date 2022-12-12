#ifndef CYLINDER_H
#define CYLINDER_H

#include <algorithm>
#include <iostream>

#include "../plane/plane.h"
#include "../shape.h"
enum INTERSECTION_TYPE {
    CYLINDER_SURFACE,
    BASE_SURFACE,
    TOP_SURFACE,
};

class Cylinder : public Shape {
   public:
    Cylinder(Reflexivity reflexivity, Vector3d base_center, Vector3d top_center,
             double radius);

    Cylinder(Reflexivity reflexivity, Vector3d base_center, double height,
             Vector3d cylinder_direction, double radius);

    Shape * Copy();
    double intersect(Vector3d &p_0, Vector3d &dr);
    Vector3d normal(Vector3d &p_i);
    void rebuild_M();
    void operator*(AccMatrix m);
    void operator*(gMatrix m);

   private:
    Vector3d base_center_;
    Vector3d top_center_;
    Vector3d cylinder_direction;
    vector<Vector3d> M;
    double height;
    double radius_;
    bool in_cylinder_surface(Vector3d &p0, Vector3d &dr, double &t);
    bool in_lid_surface(Vector3d &p0, Vector3d &dr, double &t, Vector3d &lid);
    Vector3d *last_dr;

    INTERSECTION_TYPE type = INTERSECTION_TYPE::CYLINDER_SURFACE;
};

#endif