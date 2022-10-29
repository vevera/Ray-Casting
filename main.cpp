#include <SDL2/SDL.h>

#include <iostream>

#include "Vector3d/Vector3d.h"
#include "canvas/canvas.h"
#include "light/ambient/ambient.h"
#include "light/directional/directional.h"
#include "light/point/point_light.h"
#include "light/spot/spot.h"
#include "matrix/matrix.h"
#include "scene/scene.h"
#include "shapes/cone/cone.h"
#include "shapes/cylinder/cylinder.h"
#include "shapes/mesh/mesh.h"
#include "shapes/plane/plane.h"
#include "shapes/sphere/sphere.h"
//#include <opencv2/opencv.hpp>

//#include <Magick++.h>
using std::cout;
using namespace cv;
int main(int argc, char *argv[]) {
    // std::string image_path = samples::findFile("./texture/wood.png");
    // Mat img = imread("texture/wood.png", IMREAD_COLOR);
    // if (img.empty())
    // {
    //     std::cout << "Could not read the image: "
    //               << "image_path" << std::endl;
    //     return 1;
    // }
    // imshow("Display window", img);
    // int g = waitKey(0);
    int wCanvas, hCanvas, dJanela, rEsfera, wJanela, hJanela, nLin, nCol, z;
    Vector3d bgColor, i_f, p_f, i_a;
    wCanvas = 500;
    hCanvas = 500;
    dJanela = 25;
    rEsfera = 40;
    wJanela = 60;
    hJanela = 60;
    bgColor = Vector3d(0., 0., 0.);
    nLin = 500;
    nCol = 500;
    z = -dJanela;

    i_f = Vector3d(0.7, 0.7, 0.7);
    p_f = Vector3d(-100.0, 140.0, -20.0);
    i_a = Vector3d(0.3, 0.3, 0.3);

    std::vector<Light *> lights;

    PointLight light(&i_f, &p_f);
    Ambient ambient_light(&i_a);
    Directional d_light(&i_f, new Vector3d(0, -1, 0));
    Spot s_light(&i_f, new Vector3d(0, 0, -35), new Vector3d(0, 0.5, -1), 0.2);

    Spot s1_light(&i_f, new Vector3d(0, 0, -35), new Vector3d(0, 0, -1), 0.9);

    lights.push_back(&light);
    lights.push_back(&ambient_light);
    // lights.push_back(&d_light);
    // lights.push_back(&s_light);
    // lights.push_back(&s1_light);
    std::vector<Shape *> shapes;

    // Posicao do fotografo -------------------------------- begin

    int lx = 500;
    int ly = 450;
    int lz = 1500;

    Vector3d camera(0, 0, 0);
    Vector3d eye = Vector3d(lx, ly, lz, 1);

    Vector3d at = Vector3d(lx, ly, 1, 1);

    Vector3d up = Vector3d(lx, ly + 100, lz, 1);

    Vector3d vup = up - eye;

    Vector3d k_c = (eye - at).normalize();                 // z da camera
    Vector3d i_c = (vup.cross_product(k_c)).normalize();   // x da camera
    Vector3d j_c = (k_c.cross_product(i_c)).normalize();   // y da camera

    // matriz que vai converter para as coordenadas de camera

    std::vector<Vector3d> t_c = {
        Vector3d(i_c.get(0), i_c.get(1), i_c.get(2), -(i_c.dot(eye))),
        Vector3d(j_c.get(0), j_c.get(1), j_c.get(2), -(j_c.dot(eye))),
        Vector3d(k_c.get(0), k_c.get(1), k_c.get(2), -(k_c.dot(eye))),
        Vector3d(0, 0, 0, 1)};

    gMatrix matriz_wc(t_c, TransformType::CAMERA);

    Vector3d eye_aux = eye;
    eye *matriz_wc.transform_matrix;
    camera = eye;
    std::cout << "CAMERA: " << eye.toStr() << std::endl;

    Vector3d k_gift_a = Vector3d(1.0, 0.078, 0.576);
    Reflexivity reflex_gift(&k_gift_a, &k_gift_a, &k_gift_a, 1);

    Vector3d k_floor_a = Vector3d(0.3, 0.6, 0.1);
    Reflexivity reflex_floor(&k_floor_a, &k_floor_a, &k_floor_a, 1);

    // Objeto complexo 01 ==========================================

    Plane floor_wall(reflex_floor, Vector3d(0.0, 0.0, 0.0),
                     Vector3d(0.0, 1.0, 0.0));

    floor_wall *matriz_wc;

    Mesh suport_1(reflex_gift, "blender objects/cubo_17.obj");
    Mesh suport_2(reflex_gift, "blender objects/cubo_17.obj");
    gMatrix scale_t = Matrix::scale(Vector3d(5, 95, 150));

    auto sup1_t =
        scale_t * Matrix::translate(Vector3d(300 - 125, 47.5, 500)) * matriz_wc;

    auto sup2_t =
        scale_t * Matrix::translate(Vector3d(300 + 125, 47.5, 500)) * matriz_wc;

    suport_1 *sup1_t;
    suport_2 *sup2_t;

    Mesh lid(reflex_gift, "blender objects/cubo_17.obj");

    auto lid_t = Matrix::scale(Vector3d(250, 5, 150)) *
                 Matrix::translate(Vector3d(300, 97.5, 500)) * matriz_wc;
    lid *lid_t;

    // Objeto complexo 02 ==========================================

    Cylinder suppord_tree(reflex_gift, Vector3d(0, 0, 0), 1, Vector3d(0, 1, 0),
                          1);

    auto suppord_tree_t = Matrix::scale(Vector3d(30, 9, 1)) *
                          Matrix::translate(Vector3d(300, 100, 500)) *
                          matriz_wc;

    suppord_tree *suppord_tree_t;

    Cylinder wood_2(reflex_gift, Vector3d(0, 0, 0), 1, Vector3d(0, 1, 0), 1);

    auto wood_t = Matrix::scale(Vector3d(6, 40, 4.5)) *
                  Matrix::translate(Vector3d(300, 109, 500)) * matriz_wc;

    wood_2 *wood_t;

    Cone tree_2(reflex_gift, Vector3d(0, 0, 0), 1, Vector3d(0, 1, 0), 1);

    auto tree_t = Matrix::scale(Vector3d(60, 150, 4.5)) *
                  Matrix::translate(Vector3d(300, 149, 500)) * matriz_wc;

    tree_2 *tree_t;

    Sphere star_2(reflex_gift, Vector3d(0, 0, 0), 1);
    auto star_t = Matrix::scale(Vector3d(4.5, 4.5, 4.5)) *
                  Matrix::translate(Vector3d(300, 299, 500)) * matriz_wc;

    star_2 *star_t;

    // Objeto complexo 03 ==========================================

    gMatrix scale_column = Matrix::scale(Vector3d(50, 500, 30));
    Mesh left_column(reflex_gift, "blender objects/cubo_17.obj");
    auto left_column_t =
        scale_column * Matrix::translate(Vector3d(0, 250, 1000)) * matriz_wc;
    left_column *left_column_t;

    Mesh right_column(reflex_gift, "blender objects/cubo_17.obj");
    auto right_column_t =
        scale_column * Matrix::translate(Vector3d(600, 250, 1000)) * matriz_wc;

    right_column *right_column_t;

    Mesh back_left_column(reflex_gift, "blender objects/cubo_17.obj");
    auto back_left_column_t =
        scale_column * Matrix::translate(Vector3d(0, 250, 0)) * matriz_wc;

    back_left_column *back_left_column_t;

    Mesh back_right_column(reflex_gift, "blender objects/cubo_17.obj");
    auto back_right_column_t =
        scale_column * Matrix::translate(Vector3d(600, 250, 0)) * matriz_wc;

    back_right_column *back_right_column_t;

    // QUASE
    Mesh left_beam(reflex_gift, "blender objects/cubo_17.obj");
    auto left_beam_t = Matrix::scale(Vector3d(300, 50, 30)) *
                       Matrix::shearing(ShearTypes::XY, 42.97183) *
                       Matrix::translate(Vector3d(150, 600, 1000));

    left_beam *left_beam_t;

    Mesh right_beam = left_beam;
    auto right_beam_t = Matrix::translate(Vector3d(-150, -600, -1000)) *
                        Matrix::reflection(RPlane::YZ_PLANE) *
                        Matrix::translate(Vector3d(450, 600, 1000)) * matriz_wc;

    right_beam *(right_beam_t);
    left_beam *matriz_wc;

    Mesh back_left_beam(reflex_gift, "blender objects/cubo_17.obj");
    auto back_left_beam_t = Matrix::scale(Vector3d(300, 50, 30)) *
                            Matrix::shearing(ShearTypes::XY, 42.97183) *
                            Matrix::translate(Vector3d(150, 600, 0));

    back_left_beam *back_left_beam_t;

    Mesh back_right_beam = back_left_beam;
    auto back_right_beam_t = Matrix::translate(Vector3d(-150, -600, 0)) *
                             Matrix::reflection(RPlane::YZ_PLANE) *
                             Matrix::translate(Vector3d(450, 600, 0)) *
                             matriz_wc;

    back_right_beam *(back_right_beam_t);
    back_left_beam *matriz_wc;

    shapes.push_back(&floor_wall);
    shapes.push_back(&suport_1);
    shapes.push_back(&suport_2);
    shapes.push_back(&lid);
    shapes.push_back(&suppord_tree);
    shapes.push_back(&wood_2);
    shapes.push_back(&tree_2);
    shapes.push_back(&star_2);
    shapes.push_back(&left_column);
    shapes.push_back(&right_column);
    shapes.push_back(&back_left_column);
    shapes.push_back(&back_right_column);
    shapes.push_back(&left_beam);
    shapes.push_back(&right_beam);
    shapes.push_back(&back_left_beam);
    shapes.push_back(&back_right_beam);
    // TRABALHO 06

    // Objeto complexo 4

    // Objeto complexo 3
    // shapes.push_back(&right_column);
    // shapes.push_back(&left_column);
    // shapes.push_back(&left_beam);
    // shapes.push_back(&right_beam);
    // Objeto complexo 2

    //   Objeto complexo 1
    // shapes.push_back(&lid);

    // WINDOW

    Canvas canvas(wCanvas, hCanvas, nCol, nLin);
    Scene scene(shapes, canvas, lights);

    ViewPort vp(wJanela, hJanela, z);

    scene.take_a_picture(camera, vp, bgColor);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Cena", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, wCanvas,
                                          hCanvas, SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Surface *screen = SDL_GetWindowSurface(window);

    SDL_Surface *surf = SDL_CreateRGBSurfaceFrom(
        (void *) canvas.pixels, wCanvas, hCanvas, 24, 3 * wCanvas, 0x000000ff,
        0x0000ff00, 0x00ff0000, 0xff000000);
    SDL_Rect offset;

    // Give the offsets to the rectangle
    offset.x = 0;
    offset.y = 0;

    // Blit the surface
    SDL_BlitSurface(surf, NULL, screen, &offset);
    SDL_FreeSurface(surf);
    SDL_UpdateWindowSurface(window);

    if (NULL == surf) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event windowEvent;

    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) {
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}