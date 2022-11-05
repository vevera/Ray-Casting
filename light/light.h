#ifndef LIGHT_H
#define LIGHT_H

// class Vector3d;
class Reflexivity;
#include <Eigen/Dense>

#include "../matrix/matrix.h"

using Eigen::Vector4d;

class Light {
   protected:
    Vector4d *intensity_;

   public:
    Vector4d *position_;
    Light(Vector4d *intensity);
    Light(Vector4d *intensity, Vector4d *position);
    ~Light(){};
    Vector4d calc_diffuse_specular(Reflexivity &reflex, Vector4d &intensity,
                                   Vector4d &l, Vector4d &n, Vector4d &v,
                                   Vector4d &r);
    virtual Vector4d *get_intensity() = 0;
    virtual Vector4d *get_l(Vector4d &p) = 0;
    virtual Vector4d *get_contribution(Reflexivity &reflex, Vector4d &l,
                                       Vector4d &n, Vector4d &v,
                                       Vector4d &r) = 0;
    virtual double get_distance_from_p(Vector4d p_i) = 0;
    virtual void operator*(gMatrix m) = 0;
};

#endif