#ifndef LIGHT_H
#define LIGHT_H

class Vector3d;
class Reflexivity;
#include "../matrix/matrix.h"
#include <string>
#include <iostream>
class Light {
   protected:
    Vector3d intensity_;

   public:
    Vector3d position_;
    Light(Vector3d intensity, std::string light_name);
    Light(Vector3d intensity, Vector3d position, std::string light_name);
    ~Light(){};
    Vector3d calc_diffuse_specular(Reflexivity &reflex, Vector3d &intensity,
                                   Vector3d &l, Vector3d &n, Vector3d &v,
                                   Vector3d &r);
    virtual Vector3d get_intensity() = 0;
    virtual Vector3d get_l(Vector3d &p) = 0;
    virtual Vector3d get_contribution(Reflexivity &reflex, Vector3d &l,
                                       Vector3d &n, Vector3d &v,
                                       Vector3d &r) = 0;
    virtual long double get_distance_from_p(Vector3d p_i) = 0;
    virtual void change_some_proprety(gMatrix &wc) = 0;
    virtual std::string toStr(gMatrix &cw) = 0;
    virtual void operator*(gMatrix m) = 0;

    std::string light_name_;
};
#endif