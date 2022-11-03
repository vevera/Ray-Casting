#ifndef AMBIENT_H
#define AMBIENT_H

#include "../light.h"

class Ambient : public Light {
   public:
    Ambient(Vector3d *intensity);
    Ambient(Vector3d *intensity, Vector3d *position);
    Vector3d *get_intensity();
    Vector3d *get_l(Vector3d &p);
    Vector3d *get_contribution(Reflexivity &reflex, Vector3d &l, Vector3d &n,
                               Vector3d &v, Vector3d &r);
    double get_distance_from_p(Vector3d p_i);
    void operator*(gMatrix m){};
};

#endif