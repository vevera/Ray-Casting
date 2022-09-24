#include <iostream>

#include "Vector3d/Vector3d.h"
#include "scene/scene.h"
#include "shapes/sphere/sphere.h"
#include "shapes/plane/plane.h"
#include "shapes/cone/cone.h"
#include "canvas/canvas.h"
#include <SDL2/SDL.h>
#include "shapes/cylinder/cylinder.h"

using std::cout;

int main(int argc, char *argv[])
{
    int wCanvas, hCanvas, dJanela, rEsfera, wJanela, hJanela, nLin, nCol, z;
    Vector3d esfColor, planeColor, planeColor2, cylinderColor, coneColor, bgColor, i_f, p_f, i_a;
    wCanvas = 500;
    hCanvas = 500;
    dJanela = 30;
    rEsfera = 40;
    wJanela = 60;
    hJanela = 60;
    esfColor = Vector3d(0.0, 255.0, 0.0);
    cylinderColor = Vector3d(200.0, 200.0, 200.0);
    coneColor = Vector3d(124.0, 234.0, 200.0);
    planeColor = Vector3d(100.0, 100.0, 100.0);
    planeColor2 = Vector3d(100.0, 100.0, 100.0);
    bgColor = Vector3d(0.0, 0.0, 0.0);
    nLin = 500;
    nCol = 500;
    z = -dJanela;

    i_f = Vector3d(0.7, 0.7, 0.7);
    p_f = Vector3d(0, 60, -30);
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

    Sphere sphere(esfColor, reflex, Vector3d(0.0, 0.0, -100), rEsfera);
    Plane background(planeColor, reflex_p, Vector3d(0.0, 0.0, -300), Vector3d(0.0, 0.0, 1));
    Plane floor(planeColor, reflex_f, Vector3d(0.0, -rEsfera, 0.0), Vector3d(0.0, 1, 0.0));

    Cylinder cylinder(cylinderColor, reflex_cy, Vector3d(0.0, 0.0, -100),
                      3 * rEsfera, Vector3d(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3)), rEsfera / 3);

    Vector3d centro_cone = Vector3d(0, 0, -100) + Vector3d(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3)) * (3 * rEsfera);

    Cone cone(coneColor, reflex_c, Vector3d(0, 0, -60),
              (1.5 * 30) / 2, Vector3d(-1 / sqrt(3), 1 / sqrt(3), -1).normalize(), 1.5 * 30);

    Vector3d vertex = centro_cone;
    vertex.y_ = vertex.y_ + 50.0;

    Vector3d cc1 = centro_cone;
    cc1.z_ = cc1.z_ + 20;
    Cone cone1(coneColor, reflex_c, Vector3d(0.0, 30, -100), 30, Vector3d(0.0, 1, 0.0), rEsfera);

    Cone cone2(coneColor, reflex_c, Vector3d(0, 30, -90), 40, Vector3d(0, 1, 0), rEsfera);

    // double f, g, h;

    // std::cin >> f;
    // std::cin >> g;
    // std::cin >> h;

    // Cylinder cylinder1(esfColor, reflex_cy, Vector3d(0.0, 0.0, -100.0),
    //                    rEsfera, Vector3d(f, g, h).normalize(), rEsfera / 4);

    std::vector<Shape *> shapes;
    shapes.push_back(&background);
    shapes.push_back(&floor);
    // shapes.push_back(&sphere);
    // shapes.push_back(&cylinder);
    shapes.push_back(&cone);

    Canvas canvas(wCanvas, hCanvas, nCol, nLin);
    Scene scene(shapes, canvas, light, ambient_light);

    ViewPort vp(wJanela, hJanela, z);

    scene.take_a_picture(camera, vp, bgColor);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Cena",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          wCanvas, hCanvas,
                                          SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Surface *screen = SDL_GetWindowSurface(window);

    SDL_Surface *surf = SDL_CreateRGBSurfaceFrom((void *)canvas.pixels, wCanvas, hCanvas, 24, 3 * wCanvas,
                                                 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    SDL_Rect offset;

    // Give the offsets to the rectangle
    offset.x = 0;
    offset.y = 0;

    // Blit the surface
    SDL_BlitSurface(surf, NULL, screen, &offset);
    SDL_FreeSurface(surf);
    SDL_UpdateWindowSurface(window);

    if (NULL == surf)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event windowEvent;

    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}