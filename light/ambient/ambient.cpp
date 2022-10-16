#include "ambient.h"
#include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"

Ambient::Ambient(Vector3d *intensity) : Light(intensity){};
Ambient::Ambient(Vector3d *intensity, Vector3d *position) : Light(intensity, position){};

Vector3d *Ambient::get_intensity()
{
    return this->intensity_;
}

Vector3d *Ambient::get_l(Vector3d &p)
{
    return nullptr;
}

Vector3d *Ambient::get_contribution(Reflexivity &reflex,
                                    Vector3d &l,
                                    Vector3d &n,
                                    Vector3d &v,
                                    Vector3d &r)
{
    Vector3d *ka = reflex.ka;

    double x = this->intensity_->x_ * ka->x_;
    double y = this->intensity_->y_ * ka->y_;
    double z = this->intensity_->z_ * ka->z_;
    return new Vector3d(x, y, z);
}

double Ambient::get_distance_from_p(Vector3d p_i)
{
    return -1;
}