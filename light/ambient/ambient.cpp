#include "ambient.h"

#include "../../Vector3d/Vector3d.h"
#include "../../shapes/shape.h"

Ambient::Ambient(Vector3d intensity, std::string light_name) : Light(intensity, light_name){};
Ambient::Ambient(Vector3d intensity, Vector3d position, std::string light_name)
    : Light(intensity, position, light_name){};

Vector3d Ambient::get_intensity() { return this->intensity_; }

Vector3d Ambient::get_l(Vector3d &p) { return Vector3d(0, 0, 0); }

Vector3d Ambient::get_contribution(Reflexivity &reflex, Vector3d &l,
                                    Vector3d &n, Vector3d &v, Vector3d &r) {
    Vector3d ka = reflex.ka;
    return this->intensity_ * ka;
}

long double Ambient::get_distance_from_p(Vector3d p_i) { return -1; }

void Ambient::change_some_proprety(gMatrix &wc){

    long double x, y, z;

    std::cout << "Change Intensity" << std::endl;
   
    std::cout << "Type the intensity r, g and b values: " << std::endl<< ">> ";

    std::cin >> x;
    std::cin >> y;
    std::cin >> z;

    intensity_ = Vector3d(x, y, z);

};

std::string Ambient::toStr(gMatrix &cw){ return light_name_ ;};