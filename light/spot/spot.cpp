#include "spot.h"

#include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"

Spot::Spot(Vector3d *intensity, Vector3d *position, Vector3d *direction,
           double angle)
    : Light(intensity, position), direction_(direction), angle_(angle) {
    *this->direction_ = this->direction_->normalize();
    cos_t = std::cos(angle);
};

Vector3d *Spot::get_intensity() { return this->intensity_; }

Vector3d *Spot::get_l(Vector3d &p) {
    Vector3d *l = *this->position_ - &p;
    *l = l->normalize();
    return l;
}

Vector3d *Spot::get_contribution(Reflexivity &reflex, Vector3d &l, Vector3d &n,
                                 Vector3d &v, Vector3d &r) {
    double clds = l.dot((*this->direction_ * (-1)).normalize());

    if (clds < cos_t) {
        return new Vector3d(0, 0, 0);
    }

    Vector3d l_i = *this->intensity_ * clds;
    Vector3d cont = this->calc_diffuse_specular(reflex, l_i, l, n, v, r);

    return new Vector3d(cont.x_, cont.y_, cont.z_);
}

double Spot::get_distance_from_p(Vector3d p_i) {
    Vector3d dr = *this->position_ - p_i;
    return dr.length();
}
