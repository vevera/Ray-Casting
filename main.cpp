#include <Eigen\Core>
#include <iostream>

#include "canvas.hpp"
#include "light.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "shapes/Plane.hpp"
#include "shapes/sphere.hpp"

int main(int argc, char* argv[]) {
    constexpr uint32_t hsize = 1000;
    constexpr uint32_t wsize = 1000;

    constexpr uint32_t vhsize = 1000;
    constexpr uint32_t vwsize = 1000;

    try {
        const Vector3d eye(0, 0, 0);

        ViewPort vp{1, 1, -10};

        std::vector<Sphere> spheres;
        spheres.emplace_back(Vector3d(-1, 1, -40), 0.7,
                             Reflexivity{Vector3d(0.9, 0.1, 0.1), 6});
        spheres.emplace_back(Vector3d(1, 0, -40), 0.7,
                             Reflexivity{Vector3d(0.1, 0.1, 0.8), 6});

        std::vector<Plane> planes;
        planes.emplace_back(Vector3d(0, -1, 0), Vector3d(0, 1, 0),
                            Reflexivity{Vector3d(0.1, 0.9, 0.1), 1});
        planes.emplace_back(Vector3d(0, 0, -50), Vector3d(0, 0, 1),
                            Reflexivity{Vector3d(0.4, 0.9, 0.8), 1});
        planes.emplace_back(Vector3d(0, 1.3, 0), Vector3d(0, -1, 0),
                            Reflexivity{Vector3d(0.2, 0.3, 0.2), 1});

        std::vector<PointLight> pointlight;
        pointlight.emplace_back(Vector3d(0, 0.5, -40), Vector3d(0.5, 0.5, 0.5));
        pointlight.emplace_back(Vector3d(-10, 1, -40), Vector3d(0.5, 0.5, 0.5));

        std::vector<AmbientLight> ambientlight;
        ambientlight.emplace_back(AmbientLight{Vector3d(0.3, 0.3, 0.3)});

        Canvas canvas =
            Canvas::create("My Canvas", wsize, hsize, vwsize, vhsize);

        const auto objects =
            std::make_tuple(std::cref(planes), std::cref(spheres));

        const auto lights =
            std::make_tuple(std::cref(pointlight), std::cref(ambientlight));

        intersect(eye, canvas, vp, objects, lights);

        canvas.wait_events();

    } catch (std::exception& e) {
        std::cout << e.what();
    }

    return 0;
}