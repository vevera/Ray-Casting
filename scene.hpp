

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

template <typename ...T, typename ...L>
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

    std::tuple<double, Vector3d, Vector3d> dfct(INFINITY, Vector3d(0, 0, 0), Vector3d(0, 0, 0));
    std::tuple<double, Vector3d, Vector3d> ct = dfct;

    canvas.reset_count();

    std::cout << " dx: " << dx << " dy: " << dy << "\n";

    auto calltrace = [&](const auto& objects) {
        auto t = ray::trace(objects, p0, dr, INFINITY);

        if (std::get<0>(t) < std::get<0>(ct)) {
            ct = t;
        }
    };

    for (int l = 0; l < rows; l++) {
        yj = cyj - (dy * l);
        for (int c = 0; c < cols; c++) {
            xj = cxj + (dx * c);

            dr = Vector3d(xj, yj, vp.z) - eye;

            std::apply([&] (const auto& ... objs){ (calltrace(objs), ...); }, objects);

            if (std::get<0>(ct) != INFINITY)
                canvas.set_pixel(std::get<1>(ct));
            else
                canvas.set_pixel(Vector3d(1, 1, 1));

            ct = dfct;
        }
    }

    canvas.update_window();
}


//template <typename T>
//inline auto intersect(const Vector3d& eye, Canvas& canvas, ViewPort vp,
//                      const std::vector<T>& objects) {
//    Vector3d dr;
//    const Vector3d& p0 = eye;
//
//    uint32_t rows = canvas.row_count();
//    uint32_t cols = canvas.collumn_count();
//
//    double dx = vp.width / static_cast<double>(rows);
//    double dy = vp.height / static_cast<double>(cols);
//
//    const double cxj = (-vp.width / 2.0) + (dx / 2.0);
//    const double cyj = (vp.height / 2.0) - (dy / 2.0);
//
//    double yj, xj;
//
//    canvas.reset_count();
//
//    std::cout << " dx: " << dx << " dy: " << dy << "\n";
//
//    for (uint32_t l = 0; l < rows; l++) {
//        yj = cyj - (dy * l);
//        for (uint32_t c = 0; c < cols; c++) {
//            xj = cxj + (dx * c);
//
//            dr = Vector3d(xj, yj, vp.z) - eye;
//
//            auto t = ray::trace(objects, p0, dr, INFINITY);
//
//            if (std::get<0>(t) != INFINITY)
//                canvas.set_pixel(Vector3d(0, 0, 0));
//            else
//                canvas.set_pixel(Vector3d(1, 1, 1));
//        }
//    }
//
//    canvas.update_window();
//}

// template <typename T, typename L>
// inline void light_contribution(const T* object, const std::vector<L*>&
// lights,
//                                const Vector3d& bgcolor, const Vector3d& eye,
//                                const ViewPort& vp) {}