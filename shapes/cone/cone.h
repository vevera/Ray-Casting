#ifndef CONE_H
#define CONE_H

#include <algorithm>
#include <iostream>

#include "../plane/plane.h"
#include "../shape.h"

enum INTERSECTION_CONE_TYPE {
    CONE_SURFACE,
    BASE_CONE_SURFACE,
};

class Cone : public Shape {
   public:
    Cone(Reflexivity reflexivity, Vector4d base_center, Vector4d vertex,
         double radius, std::string texture_path = "");

    Cone(Reflexivity reflexivity, Vector4d base_center, double height,
         Vector4d cone_direction, double radius, std::string texture_path = "");

    double intersect(Vector4d &p_0, Vector4d &dr);
    Vector4d normal(Vector4d &p_i);
    void operator*(AccMatrix m);
    void operator*(gMatrix m);

   private:
    Vector4d base_center_;
    Vector4d vertex_;
    Vector4d cone_direction_;
    Vector4d *last_dr = nullptr;
    double height_;
    double radius_;
    bool in_cone_surface(Vector4d &p0, Vector4d &dr, double &t);
    bool in_base_surface(Vector4d &p0, Vector4d &dr, double &t,
                         Vector4d &base_center_);
    INTERSECTION_CONE_TYPE type = INTERSECTION_CONE_TYPE::CONE_SURFACE;
};

#endif