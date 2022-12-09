#include "spot.h"

#include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"


Spot::Spot(Vector3d intensity, Vector3d position, Vector3d direction,
           double angle, std::string light_name)
    : Light(intensity, position, light_name), direction_(direction), angle_(angle) {
    this->direction_ = this->direction_.normalize();
    cos_t = std::cos(angle);
};

Vector3d Spot::get_intensity() { return this->intensity_; }

Vector3d Spot::get_l(Vector3d &p) {
    //Vector3d l = this->position_ - &p;
    return (this->position_ - p).normalize();
}

Vector3d Spot::get_contribution(Reflexivity &reflex, Vector3d &l, Vector3d &n,
                                 Vector3d &v, Vector3d &r) {
    double clds = l.dot((this->direction_ * (-1)).normalize());

    if (clds < cos_t) {
        return Vector3d(0, 0, 0);
    }

    Vector3d l_i = this->intensity_ * clds;
    //Vector3d cont = this->calc_diffuse_specular(reflex, l_i, l, n, v, r);

    return this->calc_diffuse_specular(reflex, l_i, l, n, v, r);
}

double Spot::get_distance_from_p(Vector3d p_i) {
    Vector3d dr = this->position_ - p_i;
    return dr.length();
}

void Spot::change_some_proprety(gMatrix &wc){
    int x, y, z, index=0;


    std::cout << "1 - Change Intensity" << std::endl;
    std::cout << "2 - Change Position" << std::endl;
    std::cout << "3 - Change Direction" << std::endl;
    std::cout << "4 - Change Angle" << std::endl<< ">> ";

    

    std::cin >> index;

    if (index == 4){
        std::cin >> angle_;
        cos_t = std::cos(angle_);
        return;
    }

    std::cout << "Type the respective values: " << std::endl<< ">> ";

    std::cin >> x;
    std::cin >> y;
    std::cin >> z;

    if (index == 1)
        intensity_ = Vector3d(x, y, z);
    if (index == 2)
        position_ = Vector3d(x, y, z).mult_vector_matriz4d(wc.transform_matrix);
    if (index == 3)
        direction_ = Vector3d(x, y, z).mult_vector_matriz4d(wc.transform_matrix).normalize();

}

std::string Spot::toStr(gMatrix &cw){
    return  light_name_ + ", Position: " + position_.mult_vector_matriz4d(cw.transform_matrix).toStr() + ", Direction: " + direction_.mult_vector_matriz4d(cw.transform_matrix).toStr();
}

void Spot::operator*(gMatrix m) {

    position_ = position_.mult_vector_matriz4d(m.transform_matrix);
    direction_ = direction_.mult_vector_matriz4d(m.transform_matrix).normalize();

}