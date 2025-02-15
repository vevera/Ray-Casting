#ifndef RAY_H
#define RAY_H

#include <Eigen\Core>
#include <vector>

namespace ray {
using Eigen::Vector3d;
using Eigen::Vector4d;

template <typename T>
inline std::tuple<double, Vector3d, Vector3d> trace(const std::vector<T> &objects,
                                           const Vector3d &p0,
                                           const Vector3d &dr, double t_max) {
    double t = 0;

    struct {
        double t = INFINITY;
        size_t i = 0;
    } closest;

    for (size_t i = 0; i < objects.size(); i++) {
        t = objects[i].intersect(p0, dr);

        if (t >= 0 && t < t_max && t < closest.t) {
            closest.t = t;
            closest.i = i;
        }
    }


    return std::make_tuple(closest.t, objects[closest.i].color(),
                           Vector3d(0, 0, 0));

    //return std::make_tuple(closest.t, objects[closest.i].normal(), );
}

// Vector3d light_intensity(const std::vector<Shape *> &shapes,
//                          const std::vector<Light *> &lights, const Vector3d
//                          &n, const Vector3d &v, const Vector3d &pi, const
//                          Shape &obj, int x, int y) {
//     return Vector3d(0, 0, 0);
// }

// bool light_blocked(const std::vector<Shape *> &shapes, const Shape
// &cls_shape,
//                    const Light &light, const Vector3d &p_i,
//                    const Vector3d &lr) {
//     return true;
// }
}   // namespace ray

#endif