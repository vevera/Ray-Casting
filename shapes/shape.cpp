#include "shape.h"

#include <iostream>
Shape::Shape(Reflexivity reflexivity, Vector3d shape_center_)
    : reflexivity_(reflexivity), shape_center(shape_center_) {
};

Vector3d* Shape::kd(int x, int y) {
    
    return reflexivity_.kd;
};

Vector3d* Shape::ke(int x, int y) {
    
    return reflexivity_.ke;
};

Vector3d* Shape::ka(int x, int y) {
    
    return reflexivity_.ka;
};

double Shape::m() { return reflexivity_.m; };
