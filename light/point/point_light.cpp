#include "point_light.h"

#include <memory>

// #include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"

PointLight::PointLight(Vector4d *intensity) : Light(intensity){};
PointLight::PointLight(Vector4d *intensity, Vector4d *position)
    : Light(intensity, position){};

Vector4d *PointLight::get_intensity() { return this->intensity_; }

Vector4d *PointLight::get_l(Vector4d &p) {
    Vector4d l = *this->position_ - p;
    l = l.normalized();

    Vector4d *lp = new Vector4d(l(0), l(1), l(2), 0);
    return lp;
}

double PointLight::get_distance_from_p(Vector4d p_i) {
    Vector4d dr = *this->position_ - p_i;
    return dr.norm();
};

Vector4d *PointLight::get_contribution(Reflexivity &reflex, Vector4d &l,
                                       Vector4d &n, Vector4d &v, Vector4d &r) {
    Vector4d cont =
        this->calc_diffuse_specular(reflex, *this->intensity_, l, n, v, r);

    return new Vector4d(cont(0), cont(1), cont(2), 1);
};

void PointLight::operator*(gMatrix m) {
    *position_ = m.transform_matrix * (*position_);
};