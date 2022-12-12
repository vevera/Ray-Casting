#include "directional.h"

#include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"

Directional::Directional(Vector3d intensity, Vector3d direction, std::string light_name)
    : Light(intensity, light_name), direction_(direction.normalize()) {
    //this->direction_ = this->direction_.normalize();
};

Vector3d Directional::get_intensity() { return this->intensity_; }

Vector3d Directional::get_l(Vector3d &p) {
    //Vector3d l = (this->direction_ * -1).normalize();
    return (this->direction_ * -1.0).normalize();
}

Vector3d Directional::get_contribution(Reflexivity &reflex, Vector3d &l,
                                        Vector3d &n, Vector3d &v, Vector3d &r) {
    if (this->direction_.dot(n) >= 0.0001)
        return Vector3d(0, 0, 0);

    // Vector3d cont =
    //     this->calc_diffuse_specular(reflex, *this->intensity_, l, n, v, r);

    return this->calc_diffuse_specular(reflex, this->intensity_, l, n, v, r);
};

std::string Directional::toStr(gMatrix &cw){
    return  light_name_ + ", Direction: " + direction_.mult_vector_matriz4d(cw.transform_matrix).toStr();
}

long double Directional::get_distance_from_p(Vector3d p_i) { return INFINITY; }
void Directional::change_some_proprety(gMatrix &wc){


    long double x, y, z; 
    int index;

    std::cout << "1 - Change Intensity" << std::endl;
    std::cout << "2 - Change Direction" << std::endl; 
    
    std::cin >> index;
    std::cout << "Type the respective x, y and z values: " << std::endl<< ">> ";

    std::cin >> x;
    std::cin >> y;
    std::cin >> z;

    if (index == 1)
        intensity_ = Vector3d(x, y, z);
    if (index == 2)
        direction_.set(3, 0);
        direction_ = Vector3d(x, y, z).mult_vector_matriz4d(wc.transform_matrix).normalize();


};

void Directional::operator*(gMatrix m){

    direction_.set(3, 0);
    std::cout << "before mul: " << direction_.toStr() << std::endl;
    direction_ = direction_.mult_vector_matriz4d(m.transform_matrix);
    std::cout << "after mul: " << direction_.toStr() << std::endl;
    direction_ = direction_.normalize();
    std::cout << "after norm: " << direction_.toStr() << std::endl;
};