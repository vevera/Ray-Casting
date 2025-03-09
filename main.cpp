#include <Windows.h>

#include <Eigen\Core>
#include <iostream>

#include "affine.hpp"
#include "canvas.hpp"
#include "light.hpp"
#include "plane.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

#ifndef HOT_RELOADING
#define HOT_RELOADING FALSE
#endif   // !

#if HOT_RELOADING
#define HOT_RELODING

typedef void* (*GetObjects)(void);

static std::unordered_map<std::string, void*>* objs = nullptr;

static void LoadSceneObjects(void) {
    if (objs) {
        for (auto& obj : *objs) {
            if (obj.second)
                delete obj.second;
        }
        delete objs;
        objs = nullptr;
    }

    HMODULE handle = LoadLibraryW(L"Object.dll");

    if (handle) {
        FARPROC func = GetProcAddress(handle, "GetObjects");

        if (func) {
            auto* fnGetObjects = reinterpret_cast<GetObjects>(func);

            void* objects = fnGetObjects();

            if (objects) {
                objs =
                    reinterpret_cast<std::unordered_map<std::string, void*>*>(
                        objects);
            }
        }
        FreeLibrary(handle);
    }
}

constexpr char c_SphereKey[]{"SPHERE"};

template <typename T, const char* Key>
const auto& GetConstRefVector() {
    return *reinterpret_cast<std::vector<T>*>(objs->find(Key)->second);
}
#else
static void LoadSceneObjects(void) {}
#endif

template <typename... T>
auto MakeConstRefTuple(const T&... args) {
    return std::make_tuple(std::cref(args)...);
};

int main(int argc, char* argv[]) {
    constexpr uint32_t hsize = 800;
    constexpr uint32_t wsize = 800;

    try {
        const Vector3d eye(0, 0, 2000);

        ViewPort vp{6, 6, eye.z() - 6.4};

#if !HOT_RELOADING
        std::vector<Sphere> spheres;
        spheres.emplace_back(Vector3d(200, 300, -85), 80,
                             Reflexivity{Vector3d(1, 0, 0), 1},
                             LightInteraction::REFLECT);
        spheres.emplace_back(Vector3d(-200, 300, -85), 80,
                             Reflexivity{Vector3d(0.3, 0.1, 0.5), 256},
                             LightInteraction::REFLECT);
        spheres.emplace_back(Vector3d(24, 0, -305), 200,
                             Reflexivity{Vector3d(1, 1, 1), 1},
                             LightInteraction::REFLECT);
        spheres.emplace_back(Vector3d(0, -100, -75), 30,
                             Reflexivity{Vector3d(1, 0.4, 0.4), 1},
                             LightInteraction::REFLECT);

        std::vector<Plane> planes;
        planes.emplace_back(Vector3d(0, -500, 0), Vector3d(0, 1, 0),
                            Reflexivity{Vector3d(0, 0, 0.4), 256},
                            LightInteraction::REFLECT);

        double d = 600;
        Vector3d center(0, -50, -85);

        Vector3d a(center(0) + d, center(1) + d, center(2) + 300);
        Vector3d b(center(0), center(1) - d, center(2) - 250000);
        Vector3d c(center(0) - d, center(1) + d, center(2) + 300);

        std::vector<Triangle> triangles;
        triangles.emplace_back(a, b, c,
                               Reflexivity{Vector3d(0.9, 0.2, 0.3), 256},
                               LightInteraction::REFLECT);

        const auto objects = MakeConstRefTuple(triangles, planes, spheres);

#endif
        std::vector<PointLight> pointlight;
        pointlight.emplace_back(Vector3d(0, 1000, 40), Vector3d(0.5, 0.5, 0.5));
        pointlight.emplace_back(Vector3d(0, 500, 400), Vector3d(0.8, 0.8, 0.8));
        pointlight.emplace_back(Vector3d(0, 10000, 4001),
                                Vector3d(0.6, 0.6, 0.6));

        const auto lights = MakeConstRefTuple(pointlight);

        Canvas canvas = Canvas::create("My Canvas", wsize, hsize, wsize, hsize);

#if HOT_RELOADING
        LoadSceneObjects();
#endif

        while (auto event = canvas.poll_event()) {
            switch (event) {
                case Canvas::ReadyToRender:
#if HOT_RELOADING
                    const auto objects = MakeConstRefTuple(
                        GetConstRefVector<Sphere, c_SphereKey>());
#endif
                    Render(eye, canvas, vp, objects, lights);
                    break;
                case Canvas::Reload:
                    LoadSceneObjects();
                    break;
                case Canvas::Quit:
                    goto quit;
                case Canvas::NONE:
                    break;
                default:
                    break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    } catch (std::exception& e) {
        std::cout << e.what();
    }

    quit:

    return 0;
}