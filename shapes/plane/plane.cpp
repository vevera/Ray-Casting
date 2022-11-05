#include "plane.h"

Plane::Plane(Reflexivity reflexivity, Vector3d p_pi, Vector3d n,
             std::string texture_path)
    : Shape(reflexivity, texture_path), p_pi_(p_pi), n_(n){};

double Plane::intersect(Vector3d &p_0, Vector3d &dr) {
    double t;

    Vector3d w = p_0 - p_pi_;

    double den = dr.dot(n_);

    if (den == 0) {
        return INFINITY;
    }

    t = (w * -1).dot(n_) / den;

    return t;
};

Vector3d Plane::normal(Vector3d &p_i) { return n_; };

void Plane::operator*(AccMatrix m) {
    std::for_each(m.acc->begin(), m.acc->end(), [&](gMatrix &m) { *this *m; });
};
void Plane::operator*(gMatrix m) {
    switch (m.t_type) {
        case TransformType::TRANSLATE:
            p_pi_ = p_pi_.mult_vector_matriz4d(m.transform_matrix);
            break;
        case TransformType::SHEARING:
            break;
        case TransformType::SCALE:
            break;
        case TransformType::CAMERA:
            p_pi_ = p_pi_.mult_vector_matriz4d(m.transform_matrix);
            n_ = n_.mult_vector_matriz(m.transform_matrix).normalize();
            break;
        default:
            p_pi_ = p_pi_.mult_vector_matriz4d(m.transform_matrix);
            n_ = n_.mult_vector_matriz4d(m.n_fix).normalize();
            break;
    }
};