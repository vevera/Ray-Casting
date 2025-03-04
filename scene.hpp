
#ifndef SCENE_HPP
#define SCENE_HPP

#include <Eigen/Core>
#include <algorithm>
#include <chrono>
#include <execution>
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
    const Vector3d& p0 = eye;

    uint32_t rows = canvas.row_count();
    uint32_t cols = canvas.collumn_count();

    double dx = vp.width / static_cast<double>(rows);
    double dy = vp.height / static_cast<double>(cols);

    const double cxj = (-vp.width / 2.0) + (dx / 2.0);
    const double cyj = (vp.height / 2.0) - (dy / 2.0);

    canvas.reset_count();

    auto start = std::chrono::steady_clock::now();

    const auto tiles = canvas.get_tiles();

#ifdef MT
    std::for_each(std::execution::par, std::begin(tiles), std::end(tiles),
                  [&](const auto& tile) {
                      for (uint64_t l = tile.l0; l < tile.l1; l++) {
                          double yj = cyj - (dy * l);
                          for (uint64_t c = tile.c0; c < tile.c1; c++) {
                              double xj = cxj + (dx * c);

                              Vector3d dr = Vector3d(xj, yj, vp.z) - eye;
                              dr.normalize();

                              canvas.set_pixel(
                                  l, c,
                                  RayTracer<20, true>::CastRay(
                                      p0, dr, 0.9, objects, lights));
                          }
                      }
                  });
#else
    double yj = 0;
    double xj = 0;
    Vector3d dr;
    for (uint64_t l = 0; l < rows; l++) {
        yj = cyj - (dy * l);
        for (uint64_t c = 0; c < cols; c++) {
            xj = cxj + (dx * c);

            dr = Vector3d(xj, yj, vp.z) - eye;
            dr.normalize();

            canvas.set_pixel(
                l, c,
                RayTracer<20, true>::CastRay(p0, dr, 0.88, objects, lights));
        }
    }

    std::cout << "The nuber of rays traced is: " << numberOfRays << "\n";
#endif

    canvas.update_window();

    auto end = std::chrono::steady_clock::now();

 /*   std::cout << "The image took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << " milliseconds to render.\n";*/
}
#endif   // !
