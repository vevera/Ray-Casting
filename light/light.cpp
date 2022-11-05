#include "light.h"

// #include "../Vector3d/Vector3d.h"
#include "../shapes/shape.h"

Light::Light(Vector4d *intensity, Vector4d *position)
    : intensity_(intensity), position_(position){};

Light::Light(Vector4d *intensity)
    : intensity_(intensity), position_(new Vector4d(0, 0, 0, 1)){};

Vector4d Light::calc_diffuse_specular(Reflexivity &reflex, Vector4d &intensity,
                                      Vector4d &l, Vector4d &n, Vector4d &v,
                                      Vector4d &r) {
    Vector4d *kd = reflex.kd;
    Vector4d *ke = reflex.ke;
    double m = reflex.m;

    // difuse reflection

    Vector4d i_da = Vector4d(intensity(0) * (*kd)(0), intensity(1) * (*kd)(1),
                             intensity(2) * (*kd)(2), 1);

    Vector4d i_de = Vector4d(intensity(0) * (*ke)(0), intensity(1) * (*ke)(1),
                             intensity(2) * (*ke)(2), 1);

    Vector4d i_d = i_da * std::max(l.dot(n), 0.0);
    // specular reflection
    Vector4d i_e = i_de * std::max(pow(v.dot(r), m), 0.0);

    return i_d + i_e;
}