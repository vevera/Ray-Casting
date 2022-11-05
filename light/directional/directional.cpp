#include "directional.h"

// #include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"

Directional::Directional(Vector4d *intensity, Vector4d *direction)
    : Light(intensity), direction_(direction) {
    this->direction_->normalize();
};

Vector4d *Directional::get_intensity() { return this->intensity_; }

Vector4d *Directional::get_l(Vector4d &p) {
    Vector4d l = (*this->direction_ * -1).normalized();
    return new Vector4d(l(0), l(1), l(2), 0);
}

Vector4d *Directional::get_contribution(Reflexivity &reflex, Vector4d &l,
                                        Vector4d &n, Vector4d &v, Vector4d &r) {
    if (this->direction_->dot(n) >= 0)
        return new Vector4d(0, 0, 0, 1);

    Vector4d cont =
        this->calc_diffuse_specular(reflex, *this->intensity_, l, n, v, r);

    return new Vector4d(cont(0), cont(1), cont(2), 1);
}

double Directional::get_distance_from_p(Vector4d p_i) { return INFINITY; }
