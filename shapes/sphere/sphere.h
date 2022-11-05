#ifndef SPHERE_H
#define SPHERE_H

#include <algorithm>
#include <iostream>

#include "../shape.h"

class Sphere : public Shape {
   public:
    Sphere(Reflexivity reflexivity, Vector4d center, double radius,
           std::string texture_path = "");

    double intersect(Vector4d &p_0, Vector4d &dr);
    Vector4d normal(Vector4d &p_i);
    void operator*(AccMatrix m);
    void operator*(gMatrix m);

   private:
    Vector4d center_;
    double radius_;
};
#endif