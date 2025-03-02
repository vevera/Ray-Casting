

#include <Eigen/Core>
#include <optional>
#include <vector>

#include "canvas.hpp"
#include "raytracer.hpp"
#include "types.hpp"

struct ViewPort {
    int32_t width;
    int32_t height;
    int32_t z;
};

template <typename... T, typename... L>
inline auto Render(const Vector3d& eye, Canvas& canvas, ViewPort vp,
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

    std::cout << " dx: " << dx << " dy: " << dy << "\n";

    canvas.reset_count();

    for (int l = 0; l < rows; l++) {
        yj = cyj - (dy * l);
        for (int c = 0; c < cols; c++) {
            xj = cxj + (dx * c);

            dr = Vector3d(xj, yj, vp.z) - eye;
            dr.normalize();

            canvas.set_pixel(
                RayTracer<10, true>::CastRay(p0, dr, 0.6, objects, lights));
        }
    }

    canvas.update_window();
}

