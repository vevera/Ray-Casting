#ifndef AMBIENT_H
#define AMBIENT_H

#include "../light.h"

class Ambient : public Light {
   public:
    Ambient(Vector4d *intensity);
    Ambient(Vector4d *intensity, Vector4d *position);
    Vector4d *get_intensity();
    Vector4d *get_l(Vector4d &p);
    Vector4d *get_contribution(Reflexivity &reflex, Vector4d &l, Vector4d &n,
                               Vector4d &v, Vector4d &r);
    double get_distance_from_p(Vector4d p_i);
    void operator*(gMatrix m){};
};

#endif