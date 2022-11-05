#include "plane.h"

Plane::Plane(Reflexivity reflexivity, Vector4d p_pi, Vector4d n,
             std::string texture_path)
    : Shape(reflexivity, texture_path), p_pi_(p_pi), n_(n){};

double Plane::intersect(Vector4d &p_0, Vector4d &dr) {
    double t;

    Vector4d w = p_0 - p_pi_;

    double den = dr.dot(n_);

    if (den == 0) {
        return INFINITY;
    }

    t = (w * -1).dot(n_) / den;

    return t;
};

Vector4d Plane::normal(Vector4d &p_i) { return n_; };

void Plane::operator*(AccMatrix m) {
    std::for_each(m.acc->begin(), m.acc->end(), [&](gMatrix &m) { *this *m; });
};
void Plane::operator*(gMatrix m) {
    switch (m.t_type) {
        case TransformType::TRANSLATE:
            p_pi_ = m.transform_matrix * p_pi_;
            break;
        case TransformType::SHEARING:
            break;
        case TransformType::SCALE:
            break;
        case TransformType::CAMERA:
            p_pi_ = m.transform_matrix * p_pi_;
            n_ = (m.transform_matrix * n_).normalized();
            break;
        default:
            p_pi_ = m.transform_matrix * p_pi_;
            n_ = (m.n_fix * n_).normalized();
            break;
    }
};