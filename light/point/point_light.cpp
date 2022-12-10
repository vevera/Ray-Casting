#include "point_light.h"

#include <memory>

#include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"

PointLight::PointLight(Vector3d intensity, std::string light_name) : Light(intensity, light_name){};
PointLight::PointLight(Vector3d intensity, Vector3d position, std::string light_name)
    : Light(intensity, position, light_name){};

Vector3d PointLight::get_intensity() { return this->intensity_; }

Vector3d PointLight::get_l(Vector3d &p) {
    //Vector3d l = this->position_ - p;
    return (this->position_ - p).normalize();
}

double PointLight::get_distance_from_p(Vector3d p_i) {
    Vector3d dr = this->position_ - p_i;
    return dr.length();
};

Vector3d PointLight::get_contribution(Reflexivity &reflex, Vector3d &l,
                                       Vector3d &n, Vector3d &v, Vector3d &r) {
    // Vector3d cont =
    //     this->calc_diffuse_specular(reflex, this->intensity_, l, n, v, r);

    return this->calc_diffuse_specular(reflex, this->intensity_, l, n, v, r);
};

void PointLight::change_some_proprety(gMatrix &wc){

    double x, y, z;
    int index=0;

    std::cout << "Choose a proprety to change: " << std::endl;
    std::cout << "1 - Change Intensity" << std::endl;
    std::cout << "2 - Change Position" << std::endl<< ">> ";

    std::cin >> index;

    std::cout << "Type the respective x, y and z values: " << std::endl<< ">> ";

    std::cin >> x;
    std::cin >> y;
    std::cin >> z;

    if (index == 1)
        intensity_ = Vector3d(x, y, z);
    if (index == 2)
        position_ = Vector3d(x, y, z).mult_vector_matriz4d(wc.transform_matrix);
};

std::string PointLight::toStr(gMatrix &cw){

    return  light_name_ + ", Position: " + position_.mult_vector_matriz4d(cw.transform_matrix).toStr();

}

void PointLight::operator*(gMatrix m) {
    position_ = position_.mult_vector_matriz4d(m.transform_matrix);
};