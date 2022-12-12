#include "light.h"

#include "../Vector3d/Vector3d.h"
#include "../shapes/shape.h"
#include <algorithm>
Light::Light(Vector3d intensity, Vector3d position, std::string light_name)
    : intensity_(intensity), position_(position), light_name_(light_name){};

Light::Light(Vector3d intensity, std::string light_name)
    : intensity_(intensity), position_(Vector3d(0, 0, 0)), light_name_(light_name){};

Vector3d Light::calc_diffuse_specular(Reflexivity &reflex, Vector3d &intensity,
                                      Vector3d &l, Vector3d &n, Vector3d &v,
                                      Vector3d &r) {
    Vector3d kd = reflex.kd;
    Vector3d ke = reflex.ke;
    long double m = reflex.m;

    // difuse reflection
    Vector3d i_d = ((intensity * kd) * std::max((double) l.dot(n), 0.0));
    // specular reflection
    Vector3d i_e = ((intensity * ke) * std::max((double) pow(v.dot(r), m), 0.0));

    Vector3d s = i_d + i_e;

    long double max = std::max({s.x_,s.y_,s.z_});
    //i_eye = max > 1.0 ? i_eye / max : i_eye;
    return max > 1.0 ? s / max : s;
    
    //return std::min({s.get(0),s.get(1),s.get(2)});
}