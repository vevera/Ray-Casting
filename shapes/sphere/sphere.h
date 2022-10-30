#ifndef SPHERE_H
#define SPHERE_H

#include "../shape.h"
#include <iostream>
#include <algorithm>

class Sphere : public Shape {
   public:
    Sphere(Reflexivity reflexivity, Vector3d center, double radius,
           std::string texture_path = "");

    double intersect(Vector3d p_0, Vector3d dr);
    Vector3d normal(Vector3d p_i);
    void operator*(AccMatrix m);
    void operator*(gMatrix m);

   private:
    Vector3d center_;
    double radius_;
};
#endif