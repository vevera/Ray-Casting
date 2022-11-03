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

using std::cout;
int main(int argc, char *argv[]) {
    int wCanvas, hCanvas, dJanela, rEsfera, wJanela, hJanela, nLin, nCol, z;
    Vector3d bgColor, i_f, p_f, i_a;
    wCanvas = 300;
    hCanvas = 300;
    dJanela = 25;
    rEsfera = 40;
    wJanela = 60;
    hJanela = 60;
    bgColor = Vector3d(0., 0., 0.);
    nLin = 300;
    nCol = 300;
    z = -dJanela;

    i_f = Vector3d(0.7, 0.7, 0.7);
    p_f = Vector3d(300, 100, 2000.0);
    i_a = Vector3d(0.3, 0.3, 0.3);

    // lights.push_back(&d_light);
    // lights.push_back(&s_light);
    // lights.push_back(&s1_light);
    std::vector<Shape *> shapes;

    // Posicao do fotografo -------------------------------- begin
    /*
    int lx =
    */
    double lx = 500;
    double ly = 800;
    double lz = 1500;

    Vector3d camera(0, 0, 0);
    Vector3d eye = Vector3d(lx, ly, lz, 1);

    Vector3d at = Vector3d(300, 97.5, 500, 1);

    Vector3d up = Vector3d(lx, ly + 100, lz, 1);

    Vector3d vup = up - eye;

    Vector3d k_c = (eye - at).normalize();     // z da camera
    Vector3d i_c = (vup.cross_product(k_c));   // x da camera
    Vector3d j_c = (k_c.cross_product(i_c));   // y da camera

    k_c = k_c.normalize();
    i_c = i_c.normalize();
    j_c = j_c.normalize();

    // matriz que vai converter para as coordenadas de camera

    std::vector<Vector3d> t_c = {
        Vector3d(i_c.get(0), i_c.get(1), i_c.get(2), -(i_c.dot(eye))),
        Vector3d(j_c.get(0), j_c.get(1), j_c.get(2), -(j_c.dot(eye))),
        Vector3d(k_c.get(0), k_c.get(1), k_c.get(2), -(k_c.dot(eye))),
        Vector3d(0, 0, 0, 1)};

    std::cout << "Matrix: " << std::endl;

    std::for_each(begin(t_c), end(t_c),
                  [](auto v) { std::cout << v.toStr() << std::endl; });

    gMatrix matriz_wc(t_c, t_c, TransformType::CAMERA);

    Vector3d eye_aux = eye;
    eye *matriz_wc.transform_matrix;
    std::cout << "Camera: " << eye.toStr() << std::endl;
    camera = eye;

    std::vector<Light *> lights;

    PointLight light(&i_f, &p_f);
    light *matriz_wc;

    Ambient ambient_light(&i_a);
    Directional d_light(&i_f, new Vector3d(0, -1, 0));
    Spot s_light(&i_f, new Vector3d(0, 0, -35), new Vector3d(0, 0.5, -1), 0.2);

    Spot s1_light(&i_f, new Vector3d(0, 0, -35), new Vector3d(0, 0, -1), 0.9);

    lights.push_back(&light);
    lights.push_back(&ambient_light);

    // Reflexidade dos objetos
    Vector3d k_spec = Vector3d(0, 0, 0);
    Vector3d k_floor_a = Vector3d(0.3, 0.6, 0.1);
    Reflexivity reflex_floor(&k_floor_a, &k_floor_a, &k_floor_a, 1);

    Vector3d k_support_table =
        Vector3d(210.0 / 255.0, 105.0 / 255.0, 30.0 / 255.0);
    Reflexivity reflex_support_table(&k_support_table, &k_support_table,
                                     &k_support_table, 1);

    Vector3d k_lid_table = Vector3d(65.0 / 255.0, 105.0 / 255.0, 225.0 / 255.0);
    Reflexivity reflex_lid_table(&k_lid_table, &k_lid_table, &k_lid_table, 1);

    Vector3d k_tree_wood = Vector3d(139.0 / 255.0, 69.0 / 255.0, 19.0 / 255.0);
    Reflexivity reflex_tree_wood(&k_tree_wood, &k_tree_wood, &k_tree_wood, 1);

    Vector3d k_tree_support = Vector3d(1, 1, 0);

    Reflexivity reflex_support(&k_tree_support, &k_tree_support,
                               &k_tree_support, 1);

    Vector3d k_star = Vector3d(1.0, 1.0, 0.0);
    Reflexivity reflex_star(&k_star, &k_star, &k_star, 1);

    Vector3d k_tree = Vector3d(0.0, 1.0, 0.0);
    Reflexivity reflex_tree(&k_tree, &k_tree, &k_tree, 1);

    Vector3d k_wood_column =
        Vector3d(205.0 / 255.0, 133.0 / 255.0, 63.0 / 255.0);
    Reflexivity reflex_wood_column(&k_wood_column, &k_wood_column,
                                   &k_wood_column, 1);

    Vector3d k_roof = Vector3d(1, 69.0 / 255.0, 0);
    Reflexivity reflex_roof(&k_roof, &k_roof, &k_roof, 1);

    Vector3d k_wall = Vector3d(222.0 / 255.0, 184.0 / 255.0, 135.0 / 255.0);
    Reflexivity reflex_wall(&k_wall, &k_wall, &k_wall, 1);

    // Objeto complexo 01 ==========================================

    Plane floor_wall(reflex_floor, Vector3d(0.0, 0.0, 0.0),
                     Vector3d(0.0, 1.0, 0.0));

    Mesh suport_1(reflex_support_table, "blender objects/cubo_17.obj");
    Mesh suport_2(reflex_support_table, "blender objects/cubo_17.obj");
    gMatrix scale_t = Matrix::scale(Vector3d(5, 95, 150));

    auto sup1_t = scale_t * Matrix::translate(Vector3d(300 - 125, 47.5, 500));

    auto sup2_t = scale_t * Matrix::translate(Vector3d(300 + 125, 47.5, 500));

    suport_1 *sup1_t;
    suport_2 *sup2_t;

    Mesh lid(reflex_lid_table, "blender objects/cubo_17.obj");

    auto lid_t = Matrix::scale(Vector3d(250, 5, 150)) *
                 Matrix::translate(Vector3d(300, 97.5, 500));
    lid *lid_t;

    // Objeto complexo 02 ==========================================

    Cylinder suppord_tree(reflex_support, Vector3d(0, 0, 0), 1,
                          Vector3d(0, 1, 0), 1);

    auto suppord_tree_t = Matrix::scale(Vector3d(30, 9, 1)) *
                          Matrix::translate(Vector3d(300, 100, 500));

    suppord_tree *suppord_tree_t;

    Cylinder wood_2(reflex_tree_wood, Vector3d(0, 0, 0), 1, Vector3d(0, 1, 0),
                    1);

    auto wood_t = Matrix::scale(Vector3d(6, 40, 4.5)) *
                  Matrix::translate(Vector3d(300, 109, 500));

    wood_2 *wood_t;

    Cone tree_2(reflex_tree, Vector3d(0, 0, 0), 1, Vector3d(0, 1, 0), 1);

    auto tree_t = Matrix::scale(Vector3d(60, 150, 4.5)) *
                  Matrix::translate(Vector3d(300, 149, 500));

    tree_2 *tree_t;

    Sphere star_2(reflex_star, Vector3d(0, 0, 0), 1);
    auto star_t = Matrix::scale(Vector3d(4.5, 4.5, 4.5)) *
                  Matrix::translate(Vector3d(300, 299, 500));

    star_2 *star_t;

    // Objeto complexo 03 ==========================================
    auto left_column_t = Matrix::scale(Vector3d(50, 500, 30)) *
                         Matrix::translate(Vector3d(0, 250, 1000));

    Mesh left_column(reflex_wood_column, "blender objects/cubo_17.obj");
    left_column *left_column_t;

    Mesh right_column = left_column;
    right_column *Matrix::translate(Vector3d(600, 0, 0));

    Mesh back_left_column = left_column;
    back_left_column *Matrix::translate(Vector3d(0, 0, -1000));

    Mesh back_right_column = right_column;
    back_right_column *Matrix::translate(Vector3d(0, 0, -1000));

    // QUASE
    Mesh left_beam(reflex_wood_column, "blender objects/cubo_17.obj");
    auto left_beam_t = Matrix::scale(Vector3d(300, 50, 30)) *
                       Matrix::shearing(ShearTypes::XY, 42.97183) *
                       Matrix::translate(Vector3d(150, 600, 1000));
    // Matrix::scale(Vector3d(300, 50, 30)) *
    left_beam *left_beam_t;

    Mesh right_beam = left_beam;
    auto right_beam_t = Matrix::translate(Vector3d(-150, -600, -1000)) *
                        Matrix::reflection(RPlane::YZ_PLANE) *
                        Matrix::translate(Vector3d(450, 600, 1000));

    right_beam *(right_beam_t);

    Mesh back_left_beam(reflex_wood_column, "blender objects/cubo_17.obj");
    auto back_left_beam_t = Matrix::scale(Vector3d(300, 50, 30)) *
                            Matrix::shearing(ShearTypes::XY, 42.97183) *
                            Matrix::translate(Vector3d(150, 600, 0));

    back_left_beam *back_left_beam_t;

    Mesh back_right_beam = back_left_beam;
    auto back_right_beam_t = Matrix::translate(Vector3d(-150, -600, 0)) *
                             Matrix::reflection(RPlane::YZ_PLANE) *
                             Matrix::translate(Vector3d(450, 600, 0));

    back_right_beam *(back_right_beam_t);

    Mesh left_roof(reflex_roof, "blender objects/cubo_17.obj");
    auto left_roof_t = Matrix::scale(Vector3d(300, 10, 1000)) *
                       Matrix::shearing(ShearTypes::XY, 42.97183) *
                       Matrix::translate(Vector3d(150, 600, 500));
    // Matrix::scale(Vector3d(300, 50, 30)) *
    left_roof *left_roof_t;

    Mesh right_roof = left_roof;
    auto right_roof_t = Matrix::translate(Vector3d(-150, -600, -1000)) *
                        Matrix::reflection(RPlane::YZ_PLANE) *
                        Matrix::translate(Vector3d(450, 600, 1000));

    right_roof *(right_roof_t);

    Mesh left_wall(reflex_wall, "blender objects/cubo_17.obj");
    auto left_wall_t = Matrix::scale(Vector3d(20, 500, 1000)) *
                       Matrix::translate(Vector3d(0, 250, 500));

    // Matrix::scale(Vector3d(300, 50, 30)) *
    left_wall *left_wall_t;

    Mesh right_wall = left_wall;
    auto right_wall_t = Matrix::translate(Vector3d(0, -250, -500)) *
                        Matrix::translate(Vector3d(600, 250, 500));

    right_wall *(right_wall_t);

    Mesh back_wall(reflex_wood_column, "blender objects/cubo_17.obj");
    auto back_wall_t = Matrix::scale(Vector3d(600, 500, 20)) *
                       Matrix::translate(Vector3d(300, 250, 0));

    back_wall *(back_wall_t);

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
    shapes.push_back(&right_roof);
    shapes.push_back(&left_roof);
    shapes.push_back(&right_wall);
    shapes.push_back(&left_wall);
    shapes.push_back(&back_wall);

    // WINDOW

    Canvas canvas(wCanvas, hCanvas, nCol, nLin);
    Scene scene(shapes, canvas, lights, matriz_wc);

    ViewPort vp(wJanela, hJanela, z);
    std::cout << "before take a pic" << std::endl;
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
        // std::cout << "Could not create window: " << SDL_GetError() <<
        // std::endl;
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