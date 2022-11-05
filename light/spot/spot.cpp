#include "spot.h"

// #include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"

Spot::Spot(Vector4d *intensity, Vector4d *position, Vector4d *direction,
           double angle)
    : Light(intensity, position), direction_(direction), angle_(angle) {
    *this->direction_ = this->direction_->normalized();
    cos_t = std::cos(angle);
};

Vector4d *Spot::get_intensity() { return this->intensity_; }

Vector4d *Spot::get_l(Vector4d &p) {
    Vector4d l = *this->position_ - p;
    l = l.normalized();
    return new Vector4d(l(0), l(1), l(2), 0);
}

Vector4d *Spot::get_contribution(Reflexivity &reflex, Vector4d &l, Vector4d &n,
                                 Vector4d &v, Vector4d &r) {
    double clds = l.dot((*this->direction_ * (-1)).normalized());

    if (clds < cos_t) {
        return new Vector4d(0, 0, 0, 1);
    }

    Vector4d l_i = *this->intensity_ * clds;
    Vector4d cont = this->calc_diffuse_specular(reflex, l_i, l, n, v, r);

    return new Vector4d(cont(0), cont(1), cont(2), 1);
}

double Spot::get_distance_from_p(Vector4d p_i) {
    Vector4d dr = *this->position_ - p_i;
    return dr.norm();
}

void Spot::operator*(gMatrix m) {}