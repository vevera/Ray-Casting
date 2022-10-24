#include "ambient.h"

#include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"

Ambient::Ambient(Vector3d *intensity) : Light(intensity){};
Ambient::Ambient(Vector3d *intensity, Vector3d *position)
    : Light(intensity, position){};

Vector3d *Ambient::get_intensity() { return this->intensity_; }

Vector3d *Ambient::get_l(Vector3d &p) { return new Vector3d(0, 0, 0); }

Vector3d *Ambient::get_contribution(Reflexivity &reflex, Vector3d &l,
                                    Vector3d &n, Vector3d &v, Vector3d &r) {
    Vector3d *ka = reflex.ka;
    return *this->intensity_ * ka;
}

double Ambient::get_distance_from_p(Vector3d p_i) { return -1; }