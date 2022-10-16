#include "../Vector3d/Vector3d.h"
#include "light.h"
#include "../shapes/shape.h"

Light::Light(Vector3d *intensity, Vector3d *position)
    : intensity_(intensity), position_(position){};

Light::Light(Vector3d *intensity)
    : intensity_(intensity), position_(new Vector3d(0, 0, 0)){};

Vector3d Light::calc_diffuse_specular(Reflexivity &reflex,
                                      Vector3d &intensity,
                                      Vector3d &l,
                                      Vector3d &n,
                                      Vector3d &v,
                                      Vector3d &r)
{

    Vector3d *kd = reflex.kd;
    Vector3d *ke = reflex.ke;
    double m = reflex.m;

    Vector3d i_d = ((intensity * (*kd)) * std::max(l.dot(n), 0.0));
    // specular reflection
    Vector3d i_e = ((intensity * (*ke)) * std::max(pow(v.dot(r), m), 0.0));

    Vector3d cont = i_d + i_e;

    return cont;
}