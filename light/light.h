#ifndef LIGHT_H
#define LIGHT_H

// struct Light
// {
//     Vector3d *intensity;
//     Vector3d *position;
//     string type;

//     Light()
//     {
//         intensity = new Vector3d(1, 1, 1);
//         position = new Vector3d(0, 0, 0);
//         type = "point";
//     }

//     Light(Vector3d *intensity_, Vector3d *position_, string type_)
//     {
//         intensity = intensity_;
//         position = position_;
//         type = type_;
//     }

//     Light(Vector3d *intensity_)
//     {
//         intensity = intensity_;
//         position = new Vector3d(0, 0, 0);
//         type = "ambient";
//     }
// };

class Vector3d;
class Reflexivity;

class Light
{
protected:
    Vector3d *intensity_;
    Vector3d *position_;

public:
    Light(Vector3d *intensity);
    Light(Vector3d *intensity, Vector3d *position);
    ~Light(){};
    Vector3d calc_diffuse_specular(Reflexivity &reflex,
                                   Vector3d &intensity,
                                   Vector3d &l,
                                   Vector3d &n,
                                   Vector3d &v,
                                   Vector3d &r);
    virtual Vector3d *get_intensity() = 0;
    virtual Vector3d *get_l(Vector3d &p) = 0;
    virtual Vector3d *get_contribution(Reflexivity &reflex,
                                       Vector3d &l,
                                       Vector3d &n,
                                       Vector3d &v,
                                       Vector3d &r) = 0;
    virtual double get_distance_from_p(Vector3d p_i) = 0;
};

#endif