#include "sphere.h"

Sphere::Sphere(Reflexivity reflexivity, Vector3d center, double radius)
    : Shape(reflexivity, center), center_(center), radius_(radius){};

double Sphere::intersect(Vector3d &p_0, Vector3d &dr) {
    double t1 = 0, t2 = 0, a = 0, b = 0, c = 0, delta = 0;

    Vector3d w = p_0 - center_;

    a = dr.dot(dr);
    b = 2 * (w.dot(dr));
    c = w.dot(w) - pow(radius_, 2);

    delta = pow(b, 2) - 4 * a * c;

    if (delta < 0) {
        return INFINITY;
    }

    t1 = (-b + sqrt(delta)) / (2 * a);

    t2 = (-b - sqrt(delta)) / (2 * a);

    return std::min(t1, t2);
}

Vector3d Sphere::normal(Vector3d &p_i) { return (p_i - center_) / radius_; }

void Sphere::operator*(AccMatrix m) {
    std::for_each(m.acc->begin(), m.acc->end(), [&](gMatrix &m) { *this *m; });
};
void Sphere::operator*(gMatrix m) {
    switch (m.t_type) {
        case TransformType::SCALE:
            radius_ = radius_ * (m.transform_matrix.at(0).get(0) / 2);
            break;
        case TransformType::SHEARING:
            break;
        default:
            shape_center = shape_center.mult_vector_matriz4d(m.transform_matrix);
            center_ = center_.mult_vector_matriz4d(m.transform_matrix);
            break;
    }
};



Shape * Sphere::Copy(){
    return new Sphere(*this);
};
