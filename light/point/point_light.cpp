#include "point_light.h"

#include <memory>

#include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"

PointLight::PointLight(Vector3d *intensity) : Light(intensity){};
PointLight::PointLight(Vector3d *intensity, Vector3d *position)
    : Light(intensity, position){};

Vector3d *PointLight::get_intensity() { return this->intensity_; }

Vector3d *PointLight::get_l(Vector3d &p) {
    Vector3d *l = *this->position_ - &p;
    *l = l->normalize();
    return l;
}

double PointLight::get_distance_from_p(Vector3d p_i) {
    Vector3d dr = *this->position_ - p_i;
    return dr.length();
};

Vector3d *PointLight::get_contribution(Reflexivity &reflex, Vector3d &l,
                                       Vector3d &n, Vector3d &v, Vector3d &r) {
    Vector3d cont =
        this->calc_diffuse_specular(reflex, *this->intensity_, l, n, v, r);

    return new Vector3d(cont.x_, cont.y_, cont.z_);
};