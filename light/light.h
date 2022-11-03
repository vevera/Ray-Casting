#ifndef LIGHT_H
#define LIGHT_H

class Vector3d;
class Reflexivity;
#include "../matrix/matrix.h"
class Light {
   protected:
    Vector3d *intensity_;

   public:
    Vector3d *position_;
    Light(Vector3d *intensity);
    Light(Vector3d *intensity, Vector3d *position);
    ~Light(){};
    Vector3d calc_diffuse_specular(Reflexivity &reflex, Vector3d &intensity,
                                   Vector3d &l, Vector3d &n, Vector3d &v,
                                   Vector3d &r);
    virtual Vector3d *get_intensity() = 0;
    virtual Vector3d *get_l(Vector3d &p) = 0;
    virtual Vector3d *get_contribution(Reflexivity &reflex, Vector3d &l,
                                       Vector3d &n, Vector3d &v,
                                       Vector3d &r) = 0;
    virtual double get_distance_from_p(Vector3d p_i) = 0;
    virtual void operator*(gMatrix m) = 0;
};

#endif