#include <Eigen\Core>
#include <iostream>

#include "affine.hpp"
#include "canvas.hpp"
#include "light.hpp"
#include "plane.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

template <typename... T>
auto MakeConstRefTuple(const T&... args) {
    return std::make_tuple(std::cref(args)...);
};

struct MoveInfo {
    Vector3d target;
    Vector3d start;
    double speed;
    uint64_t si;
};

int main(int argc, char* argv[]) {
    constexpr uint32_t hsize = 800;
    constexpr uint32_t wsize = 800;

    try {
        const Vector3d eye(0, 0, 2000);

        ViewPort vp{6, 6, eye.z() - 6.4};

        std::vector<Sphere> spheres;
        spheres.emplace_back(Vector3d(200, 300, -85), 80,
                             Reflexivity{Vector3d(1, 0, 0), 1},
                             LightInteraction::REFLECT);
        spheres.emplace_back(Vector3d(-200, 300, -85), 80,
                             Reflexivity{Vector3d(0.3, 0.1, 0.5), 256},
                             LightInteraction::REFLECT);
        spheres.emplace_back(Vector3d(24, 0, -305), 200,
                             Reflexivity{Vector3d(1, 1, 1), 1},
                             LightInteraction::NONE);
        spheres.emplace_back(Vector3d(0, -100, -75), 30,
                             Reflexivity{Vector3d(1, 0.4, 0.4), 1},
                             LightInteraction::NONE);

        std::vector<Plane> planes;
        planes.emplace_back(Vector3d(0, -500, 0), Vector3d(0, 1, 0),
                            Reflexivity{Vector3d(0, 0, 0.4), 256},
                            LightInteraction::NONE);

        double d = 600;
        Vector3d center(0, -50, -85);

        Vector3d a(center(0) + d, center(1) + d, center(2) + 300);
        Vector3d b(center(0), center(1) - d, center(2) - 250000);
        Vector3d c(center(0) - d, center(1) + d, center(2) + 300);

        std::vector<Triangle> triangles;
        triangles.emplace_back(a, b, c,
                               Reflexivity{Vector3d(0.9, 0.2, 0.3), 256},
                               LightInteraction::NONE);

        std::vector<PointLight> pointlight;
        pointlight.emplace_back(Vector3d(0, 1000, 40), Vector3d(0.5, 0.5, 0.5));
        pointlight.emplace_back(Vector3d(0, 500, 400), Vector3d(0.8, 0.8, 0.8));
        pointlight.emplace_back(Vector3d(0, 10000, 4001),
                                Vector3d(0.6, 0.6, 0.6));

        Canvas canvas = Canvas::create("My Canvas", wsize, hsize, wsize, hsize);

        const auto objects = MakeConstRefTuple(triangles, planes, spheres);

        const auto lights = MakeConstRefTuple(pointlight);

        while (true) {
            auto event = canvas.poll_event();

            if (event == Canvas::Event::ReadyToRender) {
                Render(eye, canvas, vp, objects, lights);
            } else if (event == Canvas::Event::Quit) {
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    } catch (std::exception& e) {
        std::cout << e.what();
    }

    return 0;
}