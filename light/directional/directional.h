#ifndef DIRECTIONAL_H
#define DIRECTIONAL_H

#include "../light.h"

class Directional : public Light {
   private:
    Vector3d direction_;

   public:
    Directional(Vector3d intensity, Vector3d direction, std::string light_name);
    Vector3d get_intensity();
    Vector3d get_l(Vector3d &p);
    Vector3d get_contribution(Reflexivity &reflex, Vector3d &l, Vector3d &n,
                               Vector3d &v, Vector3d &r);
    long double get_distance_from_p(Vector3d p_i);
    void change_some_proprety(gMatrix &wc);
    std::string toStr(gMatrix &cw);
    void operator*(gMatrix m);
};

#endif