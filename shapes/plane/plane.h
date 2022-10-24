#ifndef PLANE_H
#define PLANE_H

#include "../shape.h"

class Plane : public Shape {
   public:
    Plane(Reflexivity reflexivity, Vector3d p_pi, Vector3d n,
          std::string texture_path = "");
    double intersect(Vector3d p_0, Vector3d dr);
    Vector3d normal(Vector3d p_i);

   private:
    Vector3d p_pi_;
    Vector3d n_;
};

#endif