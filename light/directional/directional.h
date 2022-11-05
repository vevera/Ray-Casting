#ifndef DIRECTIONAL_H
#define DIRECTIONAL_H

#include "../light.h"

class Directional : public Light {
   private:
    Vector4d *direction_;

   public:
    Directional(Vector4d *intensity, Vector4d *direction);
    Vector4d *get_intensity();
    Vector4d *get_l(Vector4d &p);
    Vector4d *get_contribution(Reflexivity &reflex, Vector4d &l, Vector4d &n,
                               Vector4d &v, Vector4d &r);
    double get_distance_from_p(Vector4d p_i);
    void operator*(gMatrix m){};
};

#endif