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
    Cylinder(Reflexivity reflexivity, Vector4d base_center, Vector4d top_center,
             double radius, std::string texture_path = "");

    Cylinder(Reflexivity reflexivity, Vector4d base_center, double height,
             Vector4d cylinder_direction, double radius,
             std::string texture_path = "");

    double intersect(Vector4d &p_0, Vector4d &dr);
    Vector4d normal(Vector4d &p_i);
    void rebuild_M();
    void operator*(AccMatrix m);
    void operator*(gMatrix m);

   private:
    Vector4d base_center_;
    Vector4d top_center_;
    Vector4d cylinder_direction;
    Eigen::Matrix3d M;
    double height;
    double radius_;
    bool in_cylinder_surface(Vector4d &p0, Vector4d &dr, double &t);
    bool in_lid_surface(Vector4d &p0, Vector4d &dr, double &t, Vector4d &lid);
    Vector4d *last_dr;

    INTERSECTION_TYPE type = INTERSECTION_TYPE::CYLINDER_SURFACE;
};

#endif