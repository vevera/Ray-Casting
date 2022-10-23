#include "directional.h"
#include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"

Directional::Directional(Vector3d *intensity, Vector3d *direction) : Light(intensity),
                                                                     direction_(direction)
{
    this->direction_->normalize();
};

Vector3d *Directional::get_intensity()
{
    return this->intensity_;
}

Vector3d *Directional::get_l(Vector3d &p)
{
    Vector3d l = (*this->direction_ * -1).normalize();
    return new Vector3d(l.x_, l.y_, l.z_);
}

Vector3d *Directional::get_contribution(Reflexivity &reflex,
                                        Vector3d &l,
                                        Vector3d &n,
                                        Vector3d &v,
                                        Vector3d &r)
{

    if (this->direction_->dot(n) >= 0)
        return new Vector3d(0, 0, 0);

    Vector3d cont = this->calc_diffuse_specular(reflex,
                                                *this->intensity_,
                                                l,
                                                n,
                                                v,
                                                r);

    return new Vector3d(cont.x_, cont.y_, cont.z_);
}

double Directional::get_distance_from_p(Vector3d p_i)
{
    return INFINITY;
}
