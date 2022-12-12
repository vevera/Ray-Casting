#ifndef SPHERE_H
#define SPHERE_H

#include <algorithm>
#include <iostream>

#include "../shape.h"

class Sphere : public Shape {
   public:
    Sphere(Reflexivity reflexivity, Vector3d center, long double radius);
    Shape * Copy();
    long double intersect(Vector3d &p_0, Vector3d &dr);
    Vector3d normal(Vector3d &p_i);
    void operator*(AccMatrix m);
    void operator*(gMatrix m);

   private:
    Vector3d center_;
    long double radius_;
};
#endif