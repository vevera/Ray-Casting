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
    esfColor = Vector3d(0.0, 200.0, 0.0);
    cylinderColor = Vector3d(200.0, 200.0, 200.0);
    coneColor = Vector3d(124.0, 234.0, 200.0);
    planeColor = Vector3d(100.0, 100.0, 100.0);
    planeColor2 = Vector3d(100.0, 100.0, 100.0);
    bgColor = Vector3d(100.0, 100.0, 100.0);
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
    ambient_light.intensity = &i_a;

    Vector3d camera(0, 0, 0);

    Reflexivity reflex;
    Vector3d k = Vector3d(0.7, 0.2, 0.2);
    reflex.kd = &k;
    reflex.ke = &k;
    reflex.ka = &k;
    reflex.m = 10;

    Reflexivity reflex_f;
    Vector3d ka_f = Vector3d(0.3, 0.3, 0.7);
    Vector3d ke = Vector3d(0.0, 0.0, 0.0);
    reflex_f.kd = &ka_f;
    reflex_f.ke = &ke;
    reflex_f.ka = &ka_f;
    reflex_f.m = 1;

    Reflexivity reflex_p;
    Vector3d ka_p = Vector3d(0.7, 0.2, 0.2);
    Vector3d ke_p = Vector3d(0.0, 0.0, 0.0);
    reflex_p.kd = &ka_p;
    reflex_p.ke = &ke_p;
    reflex_p.ka = &ka_p;
    reflex_p.m = 1;

    Reflexivity reflex_cy;
    Vector3d ka_cy = Vector3d( 0.2, 0.3, 0.8);
    reflex_cy.kd = &ka_cy;
    reflex_cy.ke = &ka_cy;
    reflex_cy.ka = &ka_cy;
    reflex_cy.m = 1;

    Reflexivity reflex_c;
    Vector3d ka_c = Vector3d( 0.8, 0.3, 0.2);
    reflex_c.kd = &ka_c;
    reflex_c.ke = &ka_c;
    reflex_c.ka = &ka_c;
    reflex_c.m = 1;

    Sphere sphere(esfColor, reflex, Vector3d(0.0, 0.0, -100), rEsfera);
    Plane background(planeColor, reflex_p, Vector3d(0.0, 0.0, -200), Vector3d(0.0, 0.0, 1));
    Plane floor(planeColor, reflex_f, Vector3d(0.0, -rEsfera, 0.0), Vector3d(0.0, 1, 0.0));

    Cylinder cylinder(cylinderColor, reflex_cy, Vector3d(0.0, 0.0, -100),
                      3 * rEsfera, Vector3d(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3)), rEsfera / 3);
    // centro da base localizado no centro do topo do cilindro
    // raio da base igual a 1.5 do raio da esfera
    // altura do cone igual a 1/3 do raio da base
    // vetor direção é bem complicadinho, é parecido com o do outro, é igual ao do outro (cilindro)
    // coeficiente 
    Vector3d centro_cone = Vector3d(0.0, 0.0, -100) + Vector3d(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3))*(3*rEsfera);
    Cone cone(coneColor, reflex, centro_cone,
                      rEsfera/2, Vector3d(-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3)), 1.5*rEsfera);
    Cone coneTest(esfColor, reflex_c, Vector3d(0.0, 0.0, -100.0),
                rEsfera, Vector3d(1 / sqrt(3), -1 / sqrt(3), 1 / sqrt(3)), rEsfera);

    std::vector<Shape *> shapes;
    shapes.push_back(&background);
    shapes.push_back(&floor);
    shapes.push_back(&sphere);
    shapes.push_back(&cylinder);
    shapes.push_back(&cone);
    //shapes.push_back(&coneTest);

    Canvas canvas(wCanvas, hCanvas, nCol, nLin);
    Scene scene(shapes, canvas, light, ambient_light);

    ViewPort vp;
    vp.width = wJanela;
    vp.height = hJanela;
    vp.z = z;

    scene.take_a_picture(camera, vp, bgColor);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("My Game Window",
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