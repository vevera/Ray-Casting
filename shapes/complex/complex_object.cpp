
#include "complex_object.h"
#include <algorithm>
#include <iostream>

Vector3d Centroide(std::vector<Shape *> components){

    // long double x, y, z;
    // long double sum_x, sum_y, sum_z;
    long double size = components.size();
    Vector3d sum(0,0,0,1);
    std::for_each(begin(components),end(components), [&](Shape * shape){
        sum = sum + shape->shape_center;
    });



    return (sum / size);
}


ComplexObject::ComplexObject(std::vector<Shape *> components, Shape *wrap_shape): Shape(Reflexivity(), Centroide(components)), 
components_(components), wrap_shape_(wrap_shape){

    // long double x, y, z;
    // long double sum_x, sum_y, sum_z;
    // long double size = components.size();

    // std::for_each(begin(components),end(components), [&](Shape * shape){

    //     sum_x += shape->shape_center.get(0);
    //     sum_y += shape->shape_center.get(1);
    //     sum_z += shape->shape_center.get(2);

    // });

    // x = sum_x/size;
    // y = sum_y/size;
    // z = sum_z/size;

    // shape_center = Vector3d(x,y,z);

}

long double ComplexObject::intersect(Vector3d &p_0, Vector3d &dr){
    long double near_t = INFINITY;
    long double t;

    std::for_each(begin(components_),end(components_),[&](Shape * component){
        t = component->intersect(p_0, dr);
        if (t < near_t) {
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
     std::for_each(m.acc->begin(), m.acc->end(), [&](gMatrix &mc) { *this *mc; });
};

void ComplexObject::operator*(gMatrix m){
    std::for_each(begin(components_),end(components_),[&m](Shape * component){
        *component * m;
    });
    shape_center = shape_center.mult_vector_matriz4d(m.transform_matrix);
};


Shape * ComplexObject::Copy(){
    
    std::vector<Shape *> copy_vector;
    std::for_each(begin(components_), end(components_), [&copy_vector](Shape* aux){
        copy_vector.push_back(aux->Copy());
    });
    ComplexObject *cp = new ComplexObject(copy_vector);
    cp->shape_center = this->shape_center;
    return cp;
};

