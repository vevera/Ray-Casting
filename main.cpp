#include <Eigen\Core>
#include <iostream>

#include "canvas.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "plane.hpp"
#include "sphere.hpp"


template <typename... T>
auto MakeConstRefTuple(const T&... args) {
    return std::make_tuple(std::cref(args)...);
};

int main(int argc, char* argv[]) {
    constexpr uint32_t hsize = 1000;
    constexpr uint32_t wsize = 1000;

    try {
        const Vector3d eye(0, 0, 2000);

        ViewPort vp{6, 6, eye.z() - 6.4};

        std::vector<Sphere> spheres;
        spheres.emplace_back(Vector3d(200, 300, -105), 80,
                             Reflexivity{Vector3d(1, 0, 0), 256},
                             LightInteraction::REFLECT);
        spheres.emplace_back(Vector3d(24, 0, -305), 200,
                             Reflexivity{Vector3d(1, 1, 1), 256}, LightInteraction::REFLECT);
        spheres.emplace_back(Vector3d(0, -100, -75), 30,
                             Reflexivity{Vector3d(1, 0.4, 0.4), 256},
                             LightInteraction::REFLECT);

        std::vector<Plane> planes;
        planes.emplace_back(Vector3d(0, -500, 0), Vector3d(0, 1, 0),
                            Reflexivity{Vector3d(0, 0, 0.4), 256},
                            LightInteraction::REFLECT);
        //planes.emplace_back(Vector3d(0, 0, -3000), Vector3d(0, 0, 1),
        //                    Reflexivity{Vector3d(0.1, 0.8, 0.2), 1},
        //                    LightInteraction::NONE);

        std::vector<PointLight> pointlight;
        pointlight.emplace_back(Vector3d(0, 1000, 40), Vector3d(0.5, 0.5, 0.5));
        pointlight.emplace_back(Vector3d(0, 1000, -40), Vector3d(0.8, 0.8, 0.8));


        Canvas canvas =
            Canvas::create("My Canvas", wsize, hsize, wsize, hsize);

        const auto objects = MakeConstRefTuple(planes, spheres);

        const auto lights = MakeConstRefTuple(pointlight);

        Render(eye, canvas, vp, objects, lights);

        canvas.wait_events();

    } catch (std::exception& e) {
        std::cout << e.what();
    }

    return 0;
}