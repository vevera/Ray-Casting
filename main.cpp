#include <Eigen\Core>
#include <iostream>

#include "canvas.hpp"
#include "light.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "shapes/Plane.hpp"
#include "shapes/sphere.hpp"

int main(int argc, char* argv[]) {
    //   std::tuple<int, double, int> dd;

    //   dd = std::make_tuple(3, 2.2, 1);

    //   auto print = [](const auto t) { std::cout << t << " "; };

    //   std::apply([&](auto... t) { (print(t), ...);
    //       }, dd);

    ///*   ([] { dd;
    //       }(), ...);*/

    constexpr uint32_t size = 900;


    try {
        const Vector3d eye(0, 0, 0);

        ViewPort vp{1, 1, -10};

        std::vector<Sphere> spheres;
        spheres.emplace_back(Vector3d(-1, 0, -40), 1);

        std::vector<Plane> planes;
        planes.emplace_back(Vector3d(1, 0, -40), 1);

        std::vector<PointLight> pointlight;
        pointlight.emplace_back(PointLight{});

        std::vector<AmbientLight> ambientlight;
        ambientlight.emplace_back(AmbientLight{});

        Canvas canvas = Canvas::create("My Canvas", size, size, size, size);

        // for (int i = 0; i < 500; i++) {
        //     for (int j = 0; j < 500; j++) {
        //         canvas.set_pixel(Vector3d(1.0, 1.0, 1.0));
        //     }
        // }

        // canvas.update_window();
        // canvas.reset_count();

        const auto objects =
            std::make_tuple(std::cref(planes), std::cref(spheres));

        const auto lights = std::make_tuple(std::cref(pointlight));

        intersect(eye, canvas, vp, objects, lights);

        canvas.wait_events();

    } catch (std::exception& e) {
        std::cout << e.what();
    }

    return 0;
}