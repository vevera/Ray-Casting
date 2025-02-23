

#include <Eigen/Core>
#include <vector>

#include "canvas.hpp"
#include "ray.hpp"
#include "shapes/types.hpp"

struct ViewPort {
    int32_t width;
    int32_t height;
    int32_t z;
};

const ray::ShadingInfo default_ct{Reflexivity{Vector3d(0, 0, 0)},
                                  Vector3d{0, 0, 0}, INFINITY};

template <typename... T, typename... L>
inline auto intersect(const Vector3d& eye, Canvas& canvas, ViewPort vp,
                      const std::tuple<const T&...>& objects,
                      const std::tuple<const L&...>& lights) {
    Vector3d dr;
    const Vector3d& p0 = eye;

    uint32_t rows = canvas.row_count();
    uint32_t cols = canvas.collumn_count();

    double dx = vp.width / static_cast<double>(rows);
    double dy = vp.height / static_cast<double>(cols);

    const double cxj = (-vp.width / 2.0) + (dx / 2.0);
    const double cyj = (vp.height / 2.0) - (dy / 2.0);

    double yj, xj;

    ray::ShadingInfo ct = default_ct;

    std::cout << " dx: " << dx << " dy: " << dy << "\n";

    const auto calltrace = [&](const auto& objects) {
        auto shading_info = ray::trace(objects, p0, dr, INFINITY);

        if (shading_info.t < ct.t) {
            ct = shading_info;
        }
    };

    canvas.reset_count();

    for (int l = 0; l < rows; l++) {
        yj = cyj - (dy * l);
        for (int c = 0; c < cols; c++) {
            xj = cxj + (dx * c);

            dr = Vector3d(xj, yj, vp.z) - eye;

            std::apply([&](const auto&... objs) { (calltrace(objs), ...); },
                       objects);

            if (ct.t != INFINITY) {
                canvas.set_pixel(
                    calc_lights_contribution(ct.rfx, p0 + dr * ct.t, ct.normal,
                                             dr * -1, objects, lights));
            } else {
                canvas.set_pixel(Vector3d(1, 1, 1));
            }

            ct = default_ct;
        }
    }

    canvas.update_window();
}

template <typename... T, typename... L>
inline auto calc_lights_contribution(const Reflexivity& rfx, const Vector3d& pi,
                                     const Vector3d& normal, const Vector3d& v,
                                     const std::tuple<const T&...>& objects,
                                     const std::tuple<const L&...>& lights) {
    Vector3d ieye(0, 0, 0);
    Direction l;

    auto light_is_blocked = [&](const auto& objs) -> bool {
        for (const auto& obj : objs) {
            double t = obj.intersect(pi, l.dr);

            if (t > 0.0001 && t < l.distance)
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

    double max = ieye.maxCoeff();

    return max > 1 ? ieye / max : ieye;
};