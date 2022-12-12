#include "shape.h"

#include <iostream>
Shape::Shape(Reflexivity reflexivity, Vector3d shape_center_)
    : reflexivity_(reflexivity), shape_center(shape_center_) {
};

Vector3d Shape::kd(int x, int y) {
    
    return reflexivity_.kd;
};

Vector3d Shape::ke(int x, int y) {
    
    return reflexivity_.ke;
};

Vector3d Shape::ka(int x, int y) {
    
    return reflexivity_.ka;
};

long double Shape::m() { return reflexivity_.m; };


void Shape::set_kd(Vector3d kd) {
    reflexivity_.kd = kd;
}

void Shape::set_ke(Vector3d ke) {
    reflexivity_.ke = ke;
}

void Shape::set_ka(Vector3d ka) {
    reflexivity_.ka = ka;
}

void Shape::set_m(long double m) {
    reflexivity_.m = m;
}
