#ifndef RAY_H
#define RAY_H

#include <Eigen\Core>
#include <vector>

#include "reflexivity.hpp"
#include "types.hpp"

using Eigen::Vector3d;
using Eigen::Vector4d;

struct ShadingInfo {
    Reflexivity rfx;
    Vector3d normal;
    double t;
    LightInteraction lit;
};

template <size_t N, bool First>
struct RayTracer {
    RayTracer() = delete;
    template <typename... T, typename... L>
    inline static Vector3d CastRay(const Vector3d& p0, const Vector3d& dr,
                                   double attenuation,
                                   const std::tuple<const T&...>& objects,
                                   const std::tuple<const L&...>& lights) {
        ShadingInfo ct = {Reflexivity{Vector3d(0, 0, 0)}, Vector3d{0, 0, 0},
                          INFINITY, LightInteraction::NONE};

        std::apply(
            [&](const auto&... objs) {
                (
                    [&](const auto& objects) {
                        auto shading_info = Trace(objects, p0, dr, INFINITY);

                        if (shading_info.t < ct.t) {
                            ct = shading_info;
                        }
                    }(objs),
                    ...);
            },
            objects);

        Vector3d contrib = Vector3d(0, 0, 0);

        if (ct.t != INFINITY) {
            /*    the dr * -0.001 is useful to prevent the object from hitting
               itself due to double imprecision*/

            Vector3d pi = p0 + dr * ct.t + (dr * -0.001);
            contrib = CalculateLightsContribution(ct.rfx, pi,
                                                  ct.normal, dr * -1, objects,
                                                  lights);

            switch (ct.lit) {
                case LightInteraction::REFLECT: {
                    Vector3d ray = dr - 2 * dr.dot(ct.normal) * ct.normal;
                    ray.normalize();

                    contrib += RayTracer<N - 1, false>::CastRay(
                                   pi, ray, attenuation * attenuation, objects,
                                   lights) *
                               attenuation;
                }

                break;
                default: {
                } break;
            }
        }

        if constexpr (First) {
            contrib += ct.rfx.k.cwiseProduct(Vector3d(0.1, 0.1, 0.1));
        }

        return contrib;
    }
};

template <>
struct RayTracer<0, false> {
    RayTracer() = delete;
    template <typename... T, typename... L>
    inline static Vector3d CastRay(const Vector3d& p0, const Vector3d& dr,
                                   double att,
                                   const std::tuple<const T&...>& objects,
                                   const std::tuple<const L&...>& lights) {
        return Vector3d(0, 0, 0);
    }
};

template <typename... T, typename... L>
inline Vector3d CalculateLightsContribution(
    const Reflexivity& rfx, const Vector3d& pi, const Vector3d& normal,
    const Vector3d& v, const std::tuple<const T&...>& objects,
    const std::tuple<const L&...>& lights) {
    Vector3d ieye(0, 0, 0);
    Direction l;

    const auto light_is_blocked = [&](const auto& objs) -> bool {
        for (const auto& obj : objs) {
            double t = obj.intersect(pi, l.dr);

            if (t > 0 && t < l.distance)
                return true;
        }

        return false;
    };

    const auto get_light_contrib = [&](const auto& lghts) {
        for (const auto& light : lghts) {
            l = light.get_direction_from_p(pi);

            if (!std::apply(
                    [&](const auto&... objs) {
                        return (light_is_blocked(objs) || ...);
                    },
                    objects)) {
                ieye += light.get_light_contribution(l.dr, v, normal, rfx);
            }
        }
    };

    std::apply([&](const auto&... lghts) { (get_light_contrib(lghts), ...); },
               lights);

    return ieye;
};

template <typename T>
inline ShadingInfo Trace(const std::vector<T>& objects, const Vector3d& p0,
                         const Vector3d& dr, double t_max) {
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

    return {
        objects[closest.i].color(),
        objects[closest.i].normal(p0 + dr * closest.t),
        closest.t,
        objects[closest.i].light_interation(),
    };
}

#endif