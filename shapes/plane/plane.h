#ifndef PLANE_H
#define PLANE_H

#include "../shape.h"
#include <iostream>
#include <algorithm>
class Plane : public Shape {
   public:
    Plane(Reflexivity reflexivity, Vector3d p_pi, Vector3d n,
          std::string texture_path = "");
    double intersect(Vector3d p_0, Vector3d dr);
    Vector3d normal(Vector3d p_i);
    void operator*(AccMatrix m);
    void operator*(gMatrix m);

   private:
    Vector3d p_pi_;
    Vector3d n_;
};

#endif