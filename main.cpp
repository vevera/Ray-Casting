#include <iostream>

#include "Vector3d/Vector3d.h"
#include "scene/scene.h"
#include "shapes/sphere/sphere.h"
#include "shapes/plane/plane.h"
#include "shapes/cone/cone.h"
#include "canvas/canvas.h"
#include <SDL2/SDL.h>
#include "shapes/cylinder/cylinder.h"
#include "shapes/mesh/mesh.h"

//#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
//#include <Magick++.h>
using std::cout;
using namespace cv;
int main(int argc, char *argv[])
{

    // std::string image_path = samples::findFile("./texture/wood.png");
    Mat img = imread("wood.png", IMREAD_COLOR);
    if (img.empty())
    {
        std::cout << "Could not read the image: "
                  << "image_path" << std::endl;
        return 1;
    }
    imshow("Display window", img);
    int g = waitKey(0);
    int wCanvas, hCanvas, dJanela, rEsfera, wJanela, hJanela, nLin, nCol, z;
    Vector3d bgColor, i_f, p_f, i_a;
    wCanvas = 500;
    hCanvas = 500;
    dJanela = 25;
    rEsfera = 40;
    wJanela = 60;
    hJanela = 60;
    bgColor = Vector3d(0.5, 0.5, 0.5);
    nLin = 500;
    nCol = 500;
    z = -dJanela;

    i_f = Vector3d(0.7, 0.7, 0.7);
    // p_f = Vector3d(0, 60.0, -30.0);
    p_f = Vector3d(-100.0, 140.0, -20.0);
    // p_f = Vector3d(0.0, -120.0, -120.0);
    i_a = Vector3d(0.3, 0.3, 0.3);

    Light light(&i_f, &p_f, "point");
    Light ambient_light(&i_a);

    Vector3d camera(0, 0, 0);

    Vector3d k = Vector3d(0.3, 0.55, 0.3);
    Reflexivity reflex(&k, &k, &k, 10);

    Vector3d ka_f = Vector3d(0.2, 0.7, 0.2);
    Vector3d ke = Vector3d(0.0, 0.0, 0.0);
    Reflexivity reflex_f(&ka_f, &ke, &ka_f, 1);

    Vector3d ka_p = Vector3d(0.3, 0.3, 0.7);
    Vector3d ke_p = Vector3d(0.0, 0.0, 0.0);
    Reflexivity reflex_p(&ka_p, &ke_p, &ka_p, 1);

    Vector3d ka_cy = Vector3d(0.0, 0.9, 0.0);
    Reflexivity reflex_cy(&ka_cy, &ka_cy, &ka_cy, 1);

    Vector3d ka_c = Vector3d(0.0, 0.9, 0.0);
    Reflexivity reflex_c(&ka_c, &ka_c, &ka_c, 1);

    Sphere sphere(reflex, Vector3d(0.0, 0.0, -100), rEsfera);
    Plane background(reflex_p, Vector3d(0.0, 0.0, -300), Vector3d(0.0, 0.0, 1));
    Plane floor(reflex_f, Vector3d(0.0, -rEsfera, 0.0), Vector3d(0.0, 1, 0.0));

    Cylinder cylinder(reflex_cy, Vector3d(0.0, 0.0, -100),
                      3 * rEsfera, Vector3d(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3)), rEsfera / 3);

    Vector3d centro_cone = Vector3d(0, 0, -100) + Vector3d(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3)) * (3 * rEsfera);

    Cone cone(reflex_c, Vector3d(0, 20, -100),
              (1.5 * 50) / 2, Vector3d(0, 1, -0.5).normalize(), 1.5 * 20);

    Vector3d vertex = centro_cone;
    vertex.y_ = vertex.y_ + 50.0;

    Vector3d cc1 = centro_cone;
    cc1.z_ = cc1.z_ + 20;
    Cone cone1(reflex_c, Vector3d(0.0, 30.0, -100.0), 30, Vector3d(0.0, 1, 0.0), rEsfera);

    Cone cone2(reflex_c, Vector3d(0, 30, -90), 40, Vector3d(0, 1, 0), rEsfera);

    // TRABALHO 5 -
    // 1., 0.078., 0.576
    Vector3d k_gift_a = Vector3d(1.0, 0.078, 0.576);
    // Vector3d k_gift_e = Vector3d(0.0, 0.0, 0.0);
    // Vector3d k_gift_d = Vector3d(0.0, 0.0, 0.0);
    Reflexivity reflex_gift(&k_gift_a, &k_gift_a, &k_gift_a, 1);
    Vector3d k_wall = Vector3d(0.686, 0.933, 0.933);
    Vector3d k_ceil = Vector3d(0.933, 0.933, 0.933);
    Reflexivity reflex_wall(&k_wall, &k_wall, &k_wall, 1);
    Reflexivity reflex_ceil(&k_ceil, &k_ceil, &k_ceil, 1);

    // walls
    Plane floor_wall(reflex_p, Vector3d(0.0, -150.0, 0.0), Vector3d(0.0, 1.0, 0.0));
    Plane right_wall(reflex_wall, Vector3d(200.0, -150.0, 0.0), Vector3d(-1.0, 0.0, 0.0));
    Plane front_wall(reflex_wall, Vector3d(200.0, -150.0, -400.0), Vector3d(0.0, 0.0, 1.0));
    Plane left_wall(reflex_wall, Vector3d(-200.0, -150.0, 0.0), Vector3d(1.0, 0.0, 0.0));
    Plane ceil_wall(reflex_ceil, Vector3d(0.0, 150.0, 0.0), Vector3d(0.0, -1.0, 0.0));

    // cylinder
    Vector3d k_wood = Vector3d(0.824, 0.706, 0.549);
    Reflexivity reflex_wood(&k_wood, &k_wood, &k_wood, 1);
    Cylinder wood(reflex_wood, Vector3d(0, -150, -200), 90, Vector3d(0, 1, 0), 5);

    // cone
    // Vector3d k_tree_a = Vector3d(0.0, 0.0, 0.0);
    Vector3d k_tree_d = Vector3d(0.0, 1.0, 0.498);
    // Vector3d k_tree_e = Vector3d(0.0, 0.0, 0.0);
    Reflexivity reflex_tree(&k_tree_d, &k_tree_d, &k_tree_d, 10);
    Cone tree(reflex_tree, Vector3d(0, -60, -200), 150, Vector3d(0, 1, 0), 90);
    // Cone tree(reflex_tree, Vector3d(0, 0, -200), 150, Vector3d(0, 0, -1), 150);
    //  esfera
    Vector3d k_star = Vector3d(0.854, 0.647, 0.125);
    Reflexivity reflex_star(&k_star, &k_star, &k_star, 1);
    Sphere star(reflex_star, Vector3d(0.0, 95.0, -200), 5);

    Mesh cubo(reflex_gift, "blender objects/cubo_17.obj");

    std::vector<Shape *>
        shapes;
    // shapes.push_back(&background);
    // shapes.push_back(&floor);
    // shapes.push_back(&sphere);
    // shapes.push_back(&cylinder);
    // shapes.push_back(&cone1);

    shapes.push_back(&floor_wall);
    shapes.push_back(&right_wall);
    shapes.push_back(&front_wall);
    shapes.push_back(&left_wall);
    shapes.push_back(&ceil_wall);
    shapes.push_back(&wood);
    shapes.push_back(&tree);
    shapes.push_back(&star);
    shapes.push_back(&cubo);

    Canvas canvas(wCanvas, hCanvas, nCol, nLin);
    Scene scene(shapes, canvas, light, ambient_light);

    ViewPort vp(wJanela, hJanela, z);

    scene.take_a_picture(camera, vp, bgColor);

    // SDL_Init(SDL_INIT_EVERYTHING);

    // SDL_Window *window = SDL_CreateWindow("Cena",
    //                                       SDL_WINDOWPOS_UNDEFINED,
    //                                       SDL_WINDOWPOS_UNDEFINED,
    //                                       wCanvas, hCanvas,
    //                                       SDL_WINDOW_ALLOW_HIGHDPI);

    // SDL_Surface *screen = SDL_GetWindowSurface(window);

    // SDL_Surface *surf = SDL_CreateRGBSurfaceFrom((void *)canvas.pixels, wCanvas, hCanvas, 24, 3 * wCanvas,
    //                                              0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    // SDL_Rect offset;

    // // Give the offsets to the rectangle
    // offset.x = 0;
    // offset.y = 0;

    // // Blit the surface
    // SDL_BlitSurface(surf, NULL, screen, &offset);
    // SDL_FreeSurface(surf);
    // SDL_UpdateWindowSurface(window);

    // if (NULL == surf)
    // {
    //     std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    //     return 1;
    // }

    // SDL_Event windowEvent;

    // while (true)
    // {
    //     if (SDL_PollEvent(&windowEvent))
    //     {
    //         if (SDL_QUIT == windowEvent.type)
    //         {
    //             break;
    //         }
    //     }
    // }

    // SDL_DestroyWindow(window);
    // SDL_Quit();

    // return EXIT_SUCCESS;
}