#ifndef PLANE_H
#define PLANE_H

#include <algorithm>
#include <iostream>

#include "../shape.h"
class Plane : public Shape {
   public:
    Plane(Reflexivity reflexivity, Vector4d p_pi, Vector4d n,
          std::string texture_path = "");
    double intersect(Vector4d &p_0, Vector4d &dr);
    Vector4d normal(Vector4d &p_i);
    void operator*(AccMatrix m);
    void operator*(gMatrix m);

   private:
    Vector4d p_pi_;
    Vector4d n_;
};

#endif