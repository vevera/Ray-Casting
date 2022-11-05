#include "ambient.h"

// #include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"

Ambient::Ambient(Vector4d *intensity) : Light(intensity){};
Ambient::Ambient(Vector4d *intensity, Vector4d *position)
    : Light(intensity, position){};

Vector4d *Ambient::get_intensity() { return this->intensity_; }

Vector4d *Ambient::get_l(Vector4d &p) { return new Vector4d(0, 0, 0, 0); }

Vector4d *Ambient::get_contribution(Reflexivity &reflex, Vector4d &l,
                                    Vector4d &n, Vector4d &v, Vector4d &r) {
    Vector4d *ka = reflex.ka;

    Vector4d mul = Vector4d((*this->intensity_)(0) * (*ka)(0),
                            (*this->intensity_)(1) * (*ka)(1),
                            (*this->intensity_)(2) * (*ka)(2), 1);

    return new Vector4d(mul(0), mul(1), mul(2), 1);
}

double Ambient::get_distance_from_p(Vector4d p_i) { return -1; }