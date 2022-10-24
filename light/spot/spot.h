#ifndef SPOT_H
#define SPOT_H

#include "../light.h"

class Spot : public Light {
   private:
    Vector3d *direction_;
    double angle_;
    double cos_t;

   public:
    Spot(Vector3d *intensity, Vector3d *position, Vector3d *direction,
         double angle);
    Vector3d *get_intensity();
    Vector3d *get_l(Vector3d &p);
    Vector3d *get_contribution(Reflexivity &reflex, Vector3d &l, Vector3d &n,
                               Vector3d &v, Vector3d &r);
    double get_distance_from_p(Vector3d p_i);
};

#endif
