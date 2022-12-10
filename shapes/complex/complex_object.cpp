
#include "complex_object.h"
#include <algorithm>
#include <iostream>
ComplexObject::ComplexObject(std::vector<Shape *> components, Shape *wrap_shape): Shape(Reflexivity(), Vector3d(0,0,0,1)), components_(components), wrap_shape_(wrap_shape){}

double ComplexObject::intersect(Vector3d &p_0, Vector3d &dr){
    double near_t = INFINITY;
    double t;

    std::for_each(begin(components_),end(components_),[&](Shape * component){
        t = component->intersect(p_0, dr);
        if (t < near_t){
            last_component_ = component;
            this->set_ka(last_component_->ka(1, 1));
            this->set_kd(last_component_->kd(1, 1));
            this->set_ke(last_component_->ke(1, 1));
            near_t = t;
        }
    });

    return near_t;
};

Vector3d ComplexObject::normal(Vector3d &p_i){
    return last_component_->normal(p_i);
};

void ComplexObject::operator*(AccMatrix m){
     std::for_each(m.acc->begin(), m.acc->end(), [&](gMatrix &mc) { std::cout << "DENTRO MUL COMPLEX" << std::endl; *this *mc; });
};

void ComplexObject::operator*(gMatrix m){
    std::for_each(begin(components_),end(components_),[&m](Shape * component){
        std::cout << "DENTRO MUL COMPLEX 1" << std::endl;
        *component * m;
    });
};


