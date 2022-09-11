#include <iostream>

#include "Vector3d/Vector3d.h"
#include "scene/scene.h"
#include "shapes/sphere/sphere.h"
#include "canvas/canvas.h"
#include <SDL2/SDL.h>

using std::cout;

int main(int argc, char *argv[])
{
    int wCanvas, hCanvas, dJanela, rEsfera, wJanela, hJanela, nLin, nCol, z;
    Vector3d esfColor, planeColor, planeColor2, bgColor, i_f, p_f, i_a;
    int const width = 500;
    int const height = 500;
    wCanvas = 500;
    hCanvas = 500;
    dJanela = 30;
    rEsfera = 40;
    wJanela = 60;
    hJanela = 60;
    esfColor = Vector3d(255, 0, 0);
    planeColor = Vector3d(255, 255, 0);
    planeColor2 = Vector3d(255, 255, 0);
    bgColor = Vector3d(100, 100, 100);
    nLin = 500;
    nCol = 500;
    z = -dJanela;

    i_f = Vector3d(0.7, 0.7, 0.7);
    p_f = Vector3d(0, 60, -30);
    i_a = Vector3d(0.3, 0.3, 0.3);

    Light light;
    light.intensity = &i_f;
    light.position = &p_f;

    Light ambient_light;
    light.intensity = &i_a;

    Vector3d camera(0, 0, 0);

    Reflexivity reflex;
    Vector3d k = Vector3d(0.7, 0.2, 0.2);
    reflex.kd = &k;
    reflex.ke = &k;
    reflex.ka = &k;
    reflex.m = 10;

    Sphere sphere(esfColor, reflex, Vector3d(0, 0, -100), rEsfera);

    std::vector<Shape *> shapes;
    shapes.push_back(&sphere);

    Canvas canvas(wCanvas, hCanvas, nCol, nLin);

    Scene scene(shapes, canvas, light, ambient_light);

    ViewPort vp;
    vp.width = wJanela;
    vp.height = hJanela;
    vp.z = z;

    scene.take_a_picture(camera, vp, Vector3d(100, 100, 100));

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Surface *surf = SDL_CreateRGBSurfaceFrom((void *)data, width, height, 24, 3 * width,
                                                 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

    // SDL_Window *window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);

    if (NULL == surf)
    {
        // In the case that the window could not be made...
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

    // SDL_DestroyWindow(surf);
    SDL_Quit();

    return EXIT_SUCCESS;
}