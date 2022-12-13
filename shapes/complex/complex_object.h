#ifndef COMPLEX_OBJECT_H
#define COMPLEX_OBJECT_H

#include "../shape.h"

class ComplexObject : public Shape {
   public:
    ComplexObject(Reflexivity reflex, std::vector<Shape *> components, Shape *wrap_shape = nullptr);
    long double intersect(Vector3d &p_0, Vector3d &dr);
    Vector3d normal(Vector3d &p_i);

    Shape * Copy();

    void operator*(AccMatrix m);
    void operator*(gMatrix m);

   private:
    std::vector<Shape *> components_;
    Shape * wrap_shape_;
    Shape * last_component_;
};

#endif