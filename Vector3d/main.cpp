#include <iostream>
#include <thread>

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
#include "shapes/complex/complex_object.h"
#include <Eigen/Dense>

void Clear()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

using std::cout;

int main(int argc, char *argv[]) {
    int wCanvas, hCanvas, rEsfera, wJanela, hJanela, nLin, nCol;
    long double dJanela, zj;
    Vector3d bgColor, i_f, p_f, p_f2, i_a;
    wCanvas = 500;
    hCanvas = 500;
    dJanela = 25;
    rEsfera = 40;
    wJanela = 70;
    hJanela = 70;
    bgColor = Vector3d(16.0/255.0, 17.0/255.0, 30.0/255.0);
    nLin = 500;
    nCol = 500;
    zj = -dJanela;

    i_f = Vector3d(0.7, 0.7, 0.7);
    //p_f = Vector3d(1750, 2800, 200.0);
    p_f = Vector3d(1750, 3000, 2900);
    // p_f2 = Vector3d(300, 8000, 500.0);
    i_a = Vector3d(0.0, 0.4, 0.4);

    // lights.push_back(&d_light);
    // lights.push_back(&s_light);
    // lights.push_back(&s1_light);
    std::vector<Shape *> shapes;

    // Posicao do fotografo -------------------------------- begin
    /*
    int lx =
    */
    long double lx = 3500.000000;
    long double ly = 1000.000000;
    long double lz = 4000.000000;

    // long double lx = 1750.000000;
    // long double ly = 500.000000;
    // long double lz = 7000.000000;
    // long double lx = 1750;
    // long double ly = 500;
    // long double lz = 3000;
    //1750, 120000, -100000
    Vector3d camera(0, 0, 0);
    Vector3d eye = Vector3d(lx, ly, lz, 1.0);

    Vector3d at = Vector3d(1750.0, 200.0, 500.0, 1.0);

    Vector3d up = Vector3d(lx, ly + 100.0, lz, 1.0);

    gMatrix matriz_wc = Matrix::world_camera(eye, at, up);
    gMatrix matriz_cw = Matrix::camera_world(eye, at, up);

    eye * matriz_wc.transform_matrix;
    camera = eye;

    std::vector<Light *> lights;

    PointLight light(i_f, p_f, "Luz Pontual 1");

    Ambient ambient_light(i_a, "Luz Ambiente 1");

    //Vector3d(-1750, -120000, 100000
    Directional moon_light(Vector3d(0.5, 0.5, 0.5), Vector3d(0.0, 0.0, -1.0), "Moon Light");

    lights.push_back(&light);
    lights.push_back(&ambient_light);
    lights.push_back(&moon_light);





    /**
    
    
    

    
    */
    // START OF FINAL SCENE
    Vector3d k_moon_ = Vector3d(0.8, 0, 0.2);
    Reflexivity reflex_moon(k_moon_, Vector3d(0,0,0), Vector3d(0,0,0), 1);
    Sphere moon(reflex_moon, Vector3d(1750, 120000, -100000), 20000);
    moon.ignore_shape_ = true;
    /*
    
    
    
    */

    Vector3d k_podium_ = Vector3d(148.0/255.0, 79.0/255.0, 57.0/255.0);
    Reflexivity reflex_podium(k_podium_, k_podium_, k_podium_, 1);

    Vector3d k_bench_ = Vector3d(68.0/255.0, 14.0/255.0, 11.0/255.0);
    Reflexivity reflex_bench(k_bench_, k_bench_, k_bench_, 1);
    
    Vector3d k_church_ = Vector3d(115.0/255.0, 116/255.0, 115.0/255.0);
    Reflexivity reflex_church_tower(k_church_, k_church_, k_church_, 1);

    Vector3d k_church_bell = Vector3d(218.0/255.0, 165/255.0, 32.0/255.0);
    Reflexivity reflex_church_bell(k_church_bell, k_church_bell, k_church_bell, 10);

    Vector3d k_church_floor_ = Vector3d(50.0/255.0, 50.0/255.0, 50.0/255.0);
    Reflexivity reflex_church_floor(k_church_floor_, k_church_floor_, k_church_floor_, 1);

    Vector3d k_cross_ = Vector3d(0., 0., 0.);
    Reflexivity reflex_church_cross(k_cross_, k_cross_, k_cross_, 1);


    Vector3d k_church_roof = Vector3d(115.0/255.0, 116/255.0, 115.0/255.0);
    Reflexivity reflex_church_roof(k_church_roof, k_church_roof, k_church_roof, 1);

    Vector3d k_support_table =
        Vector3d(50.0/255.0, 20.0/255.0, 20.0/255.0);
    Reflexivity reflex_support_table(k_support_table, k_support_table,
                                     k_support_table, 1);

    /*---------------------------------------------------------------------------------*/

    Mesh left_church_front(reflex_church_tower, "blender objects/cubo_17.obj");
    auto scale_side_church = Matrix::scale(Vector3d(1100, 1800, 80));
    auto t_left_church = scale_side_church * Matrix::translate(Vector3d(550, 900, 3040));

    left_church_front * t_left_church;

    Mesh left_church_back = left_church_front;
    left_church_back * Matrix::translate(Vector3d(0, 0, -3000));

    /*---------------------------------------------------------------------------------*/

    Mesh left_church_left(reflex_church_tower, "blender objects/cubo_17.obj");
    auto scale_side_church_left = Matrix::scale(Vector3d(80, 1800, 3000));
    auto t_left_church_left = scale_side_church_left * Matrix::translate(Vector3d(40, 900, 1500));

    left_church_left * t_left_church_left;

    Mesh left_church_right = left_church_left;
    left_church_right * Matrix::translate(Vector3d(1000, 0, 0));


    /*---------------------------------------------------------------------------------*/

    Mesh right_church_front = left_church_front;
    right_church_front * Matrix::translate(Vector3d(2420, 0, 0));

    Mesh right_church_back = right_church_front;
    right_church_back * Matrix::translate(Vector3d(0, 0, -3000));

    /*---------------------------------------------------------------------------------*/

    Mesh right_church_left = left_church_left;
    right_church_left * Matrix::translate(Vector3d(2420, 0, 0));

    Mesh right_church_right = right_church_left;
    right_church_right * Matrix::translate(Vector3d(1000, 0, 0));

    /*--------------------------FLOOR CHURCH------------------------------------------*/
    /*---------------------------------------------------------------------------------*/

    Mesh church_floor(reflex_church_floor, "blender objects/cubo_17.obj");

    church_floor * ( Matrix::scale(Vector3d(3800, 30, 3300)) * Matrix::translate(Vector3d(1750, 15, 1500)));


    /*--------------------------CENTER CHURCH------------------------------------------*/
    /*---------------------------------------------------------------------------------*/

    /*--------------------------CENTER FRONT CHURCH------------------------------------------*/

    Mesh center_church_front_1(reflex_support_table, "blender objects/cubo_17.obj");

    center_church_front_1 * ( Matrix::scale(Vector3d(500, 3000, 100)) * Matrix::translate(Vector3d(1250, 1500, 3100)));

    Mesh center_church_front_2 = center_church_front_1;
    center_church_front_2 * Matrix::translate(Vector3d(1000, 0, 0));

    Mesh center_church_front_3(reflex_support_table, "blender objects/cubo_17.obj");

    center_church_front_3 * ( Matrix::scale(Vector3d(500, 1800, 100)) * Matrix::translate(Vector3d(1750, 1600, 3100)));

    Mesh center_church_back(reflex_support_table, "blender objects/cubo_17.obj");

    center_church_back * ( Matrix::scale(Vector3d(1500, 3000, 100)) * Matrix::translate(Vector3d(1750, 1500, 50)));

    Mesh center_church_left(reflex_support_table, "blender objects/cubo_17.obj"); 
    
    center_church_left * ( Matrix::scale(Vector3d(100, 1200, 3200)) * Matrix::translate(Vector3d(1050, 2400, 1600)));
    
    Mesh center_church_right = center_church_left;
    center_church_right * Matrix::translate(Vector3d(1400, 0, 0));

    Mesh left_contor(reflex_support_table, "blender objects/cubo_17.obj");
    auto left_contor_t =  Matrix::scale(Vector3d(750, 100, 100)) *
                       //Matrix::translate(Vector3d(0, 0, 0))*
                       Matrix::shearing(ShearTypes::XY, 32.97183) *
                       Matrix::translate(Vector3d(1375, 3200, 3100));

    left_contor *left_contor_t;

    Mesh right_contor = left_contor;
    auto right_contor_t = Matrix::translate(Vector3d(-1375, -3200, -3100)) *
                         Matrix::reflection(RPlane::YZ_PLANE) *
                         Matrix::translate(Vector3d(2125, 3200, 3100));

    right_contor *(right_contor_t);

    



    std::vector<Shape *> center_list;

    center_list.push_back(&center_church_front_1);
    center_list.push_back(&center_church_front_2);
    center_list.push_back(&center_church_front_3);
    center_list.push_back(&left_contor);
    center_list.push_back(&right_contor);
    // center_list.push_back(&center_church_left);
    // center_list.push_back(&center_church_right);

    ComplexObject center_tower(center_list);

    /*--------------------------ROOF CHURCH------------------------------------------*/
    /*---------------------------------------------------------------------------------*/

    Mesh left_roof_church(reflex_church_roof, "blender objects/cubo_17.obj");
    auto left_roof_church_t =  Matrix::scale(Vector3d(1000, 100, 3100)) *
                       //Matrix::translate(Vector3d(0, 0, 0))*
                       Matrix::shearing(ShearTypes::XY, 22.97183) *
                       Matrix::translate(Vector3d(500, 2000, 1550));

    left_roof_church *left_roof_church_t;

    Mesh right_roof_church = left_roof_church;
    auto right_roof_church_t = Matrix::translate(Vector3d(-500, -2000, -1500)) *
                         Matrix::reflection(RPlane::YZ_PLANE) *
                         Matrix::translate(Vector3d(3000, 2000, 1500));

    right_roof_church *(right_roof_church_t);


    Mesh left_roof_church_top(reflex_church_roof, "blender objects/cubo_17.obj");
    auto left_roof_church_top_t =  Matrix::scale(Vector3d(750, 100, 3000)) *
                       //Matrix::translate(Vector3d(0, 0, 0))*
                       Matrix::shearing(ShearTypes::XY, 32.97183) *
                       Matrix::translate(Vector3d(1375, 3200, 1600));

    left_roof_church_top *left_roof_church_top_t;

    Mesh right_roof_church_top = left_roof_church_top;
    auto right_roof_church_top_t = Matrix::translate(Vector3d(-1375, -3200, -1600)) *
                         Matrix::reflection(RPlane::YZ_PLANE) *
                         Matrix::translate(Vector3d(2125, 3200, 1600));
    
    right_roof_church_top * (right_roof_church_top_t);

    /**                 *******************************                     **/
    Mesh left_roof_church_top_1(reflex_support_table, "blender objects/cubo_17.obj");
    auto left_roof_church_top_1_t =  Matrix::scale(Vector3d(1000, 100, 3100)) *
                       Matrix::translate(Vector3d(500, 1800, 1550));

    left_roof_church_top_1 *left_roof_church_top_1_t;

    Mesh right_roof_church_top_1 = left_roof_church_top_1;
    auto right_roof_church_top_1_t = Matrix::translate(Vector3d(-500, -1800, -1500)) *
                         Matrix::reflection(RPlane::YZ_PLANE) *
                         Matrix::translate(Vector3d(3000, 1800, 1500));

    right_roof_church_top_1 *(right_roof_church_top_1_t);



    /*--------------------------CROSS CHURCH------------------------------------------*/
    /*---------------------------------------------------------------------------------*/

    

    Mesh cross_y(reflex_church_cross, "blender objects/cubo_17.obj");
    auto cross_y_t = Matrix::scale(Vector3d(50, 500, 30)) *
                         Matrix::translate(Vector3d(1750, 3800, 3000));
    cross_y *cross_y_t;

    Mesh cross_x(reflex_church_cross, "blender objects/cubo_17.obj");
    auto cross_x_t = Matrix::scale(Vector3d(500, 50, 30)) *
                         Matrix::translate(Vector3d(1750, 3900, 3000));
    cross_x *cross_x_t;

    /*--------------------------BELL CHURCH------------------------------------------*/
    /*---------------------------------------------------------------------------------*/
    Cylinder bell_wrap(reflex_church_bell, Vector3d(0, -0.5, 0),
                   Vector3d(0, 0.5, 0), 0.5);
    Mesh church_bell(reflex_church_bell, "blender objects/bell.obj", &bell_wrap);

    //bell_wrap * ( Matrix::scale(Vector3d(400, 400, 400)) * Matrix::translate(Vector3d(1750, 3000, 2900)));
    church_bell * ( Matrix::scale(Vector3d(400, 400, 400)) * Matrix::translate(Vector3d(1750, 3000, 2900)));
    
    /*--------------------------BENCH CHURCH------------------------------------------*/
    /*---------------------------------------------------------------------------------*/
    
    // Cylinder bell_wrap(reflex_church_bell, Vector3d(0, -0.5, 0),
    //                Vector3d(0, 0.5, 0), 0.5);

    //Mesh church_bench(reflex_church_bell, "blender objects/cadeira.obj");

    //bell_wrap * ( Matrix::scale(Vector3d(400, 400, 400)) * Matrix::translate(Vector3d(1750, 3000, 2900)));
    //church_bench * ( Matrix::scale(Vector3d(400, 400, 400)) * Matrix::translate(Vector3d(1750, 200, 1500)));

    Mesh church_bench_1(reflex_bench, "blender objects/cubo_17.obj");

    church_bench_1 * (Matrix::scale(Vector3d(500, 20, 100)));

    Mesh church_bench_2(reflex_bench, "blender objects/cubo_17.obj");

    church_bench_2 * (Matrix::scale(Vector3d(500, 100, 20))* Matrix::translate(Vector3d(0, 60, -50)));

    long double pern_r = 10;

    Cylinder bench_support_1(reflex_bench, Vector3d(pern_r + (-250), -10, 50 - pern_r), 50,
                   Vector3d(0, -1, 0), pern_r);
    
    Cylinder bench_support_2(reflex_bench, Vector3d(pern_r + (-250), -10, pern_r - 50), 50,
                   Vector3d(0, -1, 0), pern_r);
    
    Cylinder bench_support_3(reflex_bench, Vector3d(-pern_r + (250), -10, 50 - pern_r), 50,
                   Vector3d(0, -1, 0), pern_r);
    
    Cylinder bench_support_4(reflex_bench, Vector3d(-pern_r + (250), -10, pern_r - 50), 50,
                   Vector3d(0, -1, 0), pern_r);

    std::vector<Shape *> bench_1;
    bench_1.push_back(&church_bench_1);
    bench_1.push_back(&church_bench_2);
    bench_1.push_back(&bench_support_1);
    bench_1.push_back(&bench_support_2);
    bench_1.push_back(&bench_support_3);
    bench_1.push_back(&bench_support_4);

    


    ComplexObject church_bench_00(bench_1);

    // ComplexObject church_bench_01 = church_bench_00;

    // ComplexObject church_bench_02= church_bench_00;

    Shape *church_bench_10 = church_bench_00.Copy();

    // ComplexObject church_bench_11= church_bench_00;

    // ComplexObject church_bench_12= church_bench_00;

    church_bench_00 * ( Matrix::scale(Vector3d(1, 1, 1)) * Matrix::rotate(TAxis::Y_AXIS, 180)* Matrix::translate(Vector3d(1400, 95, 1500)));
    // church_bench_01 * ( Matrix::scale(Vector3d(1, 1, 1)) * Matrix::translate(Vector3d(1400, 100, 1700)));
    // church_bench_02 * ( Matrix::scale(Vector3d(1, 1, 1)) * Matrix::translate(Vector3d(1400, 100, 1900)));

    (*church_bench_10) * ( Matrix::scale(Vector3d(1, 1, 1)) * Matrix::rotate(TAxis::Y_AXIS, 180)* Matrix::translate(Vector3d(2100, 95, 1500)));
    // church_bench_11 * ( Matrix::scale(Vector3d(1, 1, 1)) * Matrix::translate(Vector3d(2100, 100, 1700)));
    // church_bench_12 * ( Matrix::scale(Vector3d(1, 1, 1)) * Matrix::translate(Vector3d(2100, 100, 1900)));

    
    // Cylinder church_bench_3(reflex_church_bell, Vector3d(-100, -65, 30),
    //                Vector3d(-100, -5, 30), 10);
    
    // Cylinder church_bench_4(reflex_church_bell, Vector3d(100, -65, 30),
    //                Vector3d(100, -5, 30), 10);
    
    /*---------------------------------------------------------------------------------*/
    /*--------------------------CANDLE CHURCH------------------------------------------*/

    Cylinder candle(reflex_church_bell, Vector3d(0, -0.5, 0),
                   Vector3d(0, 0.5, 0), 0.5);

    /*---------------------------------------------------------------------------------*/
    /*--------------------------TABLE CHURCH------------------------------------------*/

    Mesh table(reflex_church_cross, "blender objects/cubo_17.obj");


    /*---------------------------------------------------------------------------------*/
    /*--------------------------PODIUM CHURCH------------------------------------------*/

    Mesh podium(reflex_podium, "blender objects/cubo_17.obj");
    podium * ( Matrix::scale(Vector3d(2500, 200, 800)) * Matrix::translate(Vector3d(1750, 150, 700)));


    /*---------------------------------------------------------------------------------*/
    /*--------------------------REFLECTORS CHURCH------------------------------------------*/
    // Vector3d(-1050, 1350, 1150)
    //Cone reflector1(Reflexivity(), (Vector3d(-1050, 1350, 1150).normalize() * -1),
    //               Vector3d(700, 1750, 1850), 1);

    Cone reflector1(Reflexivity(), Vector3d(0, 0, 0), 1 ,Vector3d(-1050, 1350, 1150).normalize(), 1);
    
    Cone reflector2(Reflexivity(), Vector3d(0, -0.5, 0),
                   Vector3d(0, 0.5, 0), 0.5);
    
    reflector1 * ( Matrix::scale(Vector3d(100, 100, 100)) 
        * Matrix::translate(Vector3d(700, 1750, 1850) + (Vector3d(-1050, 1350, 1150).normalize() * -100)));
    
    reflector2 = reflector1;

    reflector2 * (Matrix::reflection(RPlane::YZ_PLANE) * Matrix::translate(Vector3d(700 + 2800, 0, 0)));


    Spot spot_light_1(5, i_a,reflector1.base_center_ + Vector3d(-10, -10, -10), Vector3d(1750, 150, 700),  "Luz spot 1");

    Spot spot_light_2(5, i_a,reflector2.base_center_ + Vector3d(-10, -10, -10), Vector3d(1750, 150, 700), "Luz spot 2");

    lights.push_back(&spot_light_1);
    lights.push_back(&spot_light_2);

    /*---------------------------------------------------------------------------------*/


    // END OF FINAL SCENE
    /**
    
    
    
    
    
    */


    // Reflexidade dos objetos
    Vector3d k_spec = Vector3d(0, 0, 0);
    Vector3d k_floor_a = Vector3d(0.0, 40/255.0, 0.0);
    Reflexivity reflex_floor(k_floor_a, k_floor_a, k_floor_a, 1);

    // Objeto complexo 01 ==========================================

    Plane floor_wall(reflex_floor, Vector3d(0.0, 0.0, 0.0),
                     Vector3d(0.0, 1.0, 0.0));

    //MOON
    shapes.push_back(&moon);

    shapes.push_back(&floor_wall);
    //LEFT CHURCH
    shapes.push_back(&left_church_front);
    shapes.push_back(&left_church_back);
    shapes.push_back(&left_church_left);
    //shapes.push_back(&left_church_right);
    //RIGHT CHURCH
    shapes.push_back(&right_church_front);
    shapes.push_back(&right_church_back);
    //shapes.push_back(&right_church_left);
    shapes.push_back(&right_church_right);
    //CENTER CHURCH
    shapes.push_back(&center_tower);
    // shapes.push_back(&center_church_front);
    shapes.push_back(&center_church_back);
    shapes.push_back(&center_church_left);
    shapes.push_back(&center_church_right);
    //LATERAL ROOF CHURCH
    shapes.push_back(&right_roof_church);
    shapes.push_back(&left_roof_church);
    //TOP ROOF CHURCH
    shapes.push_back(&right_roof_church_top);
    shapes.push_back(&left_roof_church_top);
    shapes.push_back(&right_roof_church_top_1);
    shapes.push_back(&left_roof_church_top_1);
    //CROSS CHURCH
    shapes.push_back(&cross_y);
    shapes.push_back(&cross_x);
    //FLOOR CHURCH
    shapes.push_back(&church_floor);
    //BELL CHURCH
    //shapes.push_back(&bell_wrap);
    shapes.push_back(&church_bell);
    //PODIUM CHURCH
    shapes.push_back(&podium);
    //REFLECTORS CHURCH
    shapes.push_back(&reflector1);
    shapes.push_back(&reflector2);
    // BENCH CHURCH
    shapes.push_back(&church_bench_00);
    // shapes.push_back(&church_bench_01);
    // shapes.push_back(&church_bench_02);
    shapes.push_back(church_bench_10);
    // shapes.push_back(&church_bench_11);
    // shapes.push_back(&church_bench_12);



    // shapes.push_back(&lid);
    // shapes.push_back(&suppord_tree);
    // shapes.push_back(&wood_2);
    // shapes.push_back(&tree_2);
    // shapes.push_back(&star_2);
    // shapes.push_back(&left_column);
    // shapes.push_back(&right_column);
    // shapes.push_back(&back_left_column);
    // shapes.push_back(&back_right_column);
    // shapes.push_back(&left_beam);
    // shapes.push_back(&back_left_beam);
    // shapes.push_back(&back_right_beam);
    // shapes.push_back(&right_roof);
    // shapes.push_back(&left_roof);
    // shapes.push_back(&right_wall);
    // shapes.push_back(&left_wall);
    // shapes.push_back(&back_wall);
    
    //  WINDOW

    Canvas canvas(wCanvas, hCanvas, nCol, nLin);

    Scene scene(shapes, canvas, lights, matriz_wc);
    ViewPort vp(wJanela, hJanela, zj);
    scene.take_a_picture(camera, vp, bgColor);

    canvas.init_window();
    canvas.update_window();

    Shape *pick_shape;

    Vector3d *clicked_point = new Vector3d(0,0,0);

    long double dx = vp.width / (long double) canvas.n_cols();
    long double dy = vp.height / (long double) canvas.n_rows();

    std::thread object_operations([&]() {

        int option, index_, light_index;
        long double x, y, z, angle, angle_shear, m;
        TAxis axis;
        ShearTypes shear_type;
        RPlane r_plane;
        Projection projection_type;
        bool obj_transformed = true;
        Vector3d new_property;
        gMatrix temp;

        bool quit_ = false;

        while (!quit_) {
            obj_transformed = true;
            Clear();
            std::cout << "1 - Translate" << std::endl;
            std::cout << "2 - Scale" << std::endl;
            std::cout << "3 - Rotate" << std::endl;
            std::cout << "4 - Shear" << std::endl;
            std::cout << "5 - Mirroring" << std::endl;
            std::cout << "6 - Change ViewPort Distace" << std::endl;
            std::cout << "7 - Change Projection" << std::endl;
            std::cout << "8 - Change window size" << std::endl;
            std::cout << "9 - Change material property" << std::endl;
            std::cout << "10 - Change property of lights" << std::endl;
            std::cout << "11 - Change camera parameters" << std::endl;
            std::cout << "12 - Quit" << std::endl;
            std::cout << ">> ";
            
            std::cin >> option;

            AccMatrix transform_m;

            switch (option) {
                case 1:
                    x, y, z = 0;
                    std::cout << "Type position: "<< std::endl << ">> ";
                    std::cin >> x;
                    std::cin >> y;
                    std::cin >> z;
                    transform_m = Matrix::translate(Vector3d(x, y, z));
                    break;
                case 2:
                    x, y, z = 1;
                    std::cout << "Type scale: "<< std::endl << ">> ";
                    std::cin >> x;
                    std::cin >> y;
                    std::cin >> z;
                    transform_m = Matrix::translate(pick_shape->shape_center * -1) * Matrix::scale(Vector3d(x, y, z)) * Matrix::translate(pick_shape->shape_center);
                    //transform_m = Matrix::scale(Vector3d(x, y, z));
                    
                    break;
                case 3:
                    std::cout << "Type the rotate angle: " << std::endl<< ">> ";
                    std::cin >> angle;
                    std::cout << "Type the rotate axis: " << std::endl;
                    std::cout << "1 - X_AXIS: " << std::endl;
                    std::cout << "2 - Y_AXIS: " << std::endl;
                    std::cout << "3 - Z_AXIS: " << std::endl<< ">> ";
                    std::cin >> index_;
                    switch (index_) {
                        case 1:
                            axis = TAxis::X_AXIS ;
                            break;
                        case 2:
                            axis = TAxis::Y_AXIS ;
                            break;
                        case 3:
                            axis = TAxis::Z_AXIS ;
                            break;
                        default:
                            continue;
                    }
                    transform_m =  matriz_cw * 
                                   Matrix::translate(pick_shape->shape_center.mult_vector_matriz4d(matriz_cw.transform_matrix) * -1)  * 
                                   Matrix::rotate(axis, angle) * 
                                   Matrix::translate(pick_shape->shape_center.mult_vector_matriz4d(matriz_cw.transform_matrix)) * 
                                   matriz_wc;
                    break;
                case 4:
                    std::cout << clicked_point->toStr() << std::endl;
                    std::cout << pick_shape->shape_center.toStr() << std::endl;
                    std::cout << Vector3d(150, 600, 1000).mult_vector_matriz4d(matriz_wc.transform_matrix).toStr() << std::endl;
                    std::cout << "Type the rotate angle: " << std::endl<< ">> ";
                    std::cin >> angle_shear;
                    std::cout << "Type the shear: " << std::endl;
                    std::cout << "1 - XZ: \n2 - ZX: \n3 - XY: \n4 - YX: \n5 - ZY: \n6 - YZ: \n"<< ">> ";
                    std::cin >> index_;
                    switch (index_) {
                        case 1:
                            shear_type = ShearTypes::XZ ;
                            break;
                        case 2:
                            shear_type = ShearTypes::ZX ;
                            break;
                        case 3:
                            shear_type = ShearTypes::XY ;
                            break;
                        case 4:
                            shear_type = ShearTypes::YX ;
                            break;
                        case 5:
                            shear_type = ShearTypes::ZY ;
                            break;
                        case 6:
                            shear_type = ShearTypes::YZ ;
                            break;
                        default:
                            continue;
                    }
                    transform_m = matriz_cw * 
                                  Matrix::translate(pick_shape->shape_center.mult_vector_matriz4d(matriz_cw.transform_matrix) * -1) * 
                                  Matrix::shearing(shear_type, angle_shear) * 
                                  Matrix::translate(pick_shape->shape_center.mult_vector_matriz4d(matriz_cw.transform_matrix)) * 
                                  matriz_wc;
                    break;
                case 5:
                    std::cout << "Type the shear: " << std::endl;
                    std::cout << "1 - Plane XY: " << std::endl;
                    std::cout << "2 - Plane YZ: " << std::endl;
                    std::cout << "3 - Plane XZ: " << std::endl<< ">> ";
                    std::cin >> index_;
                    switch (index_) {
                        case 1:
                            r_plane = RPlane::XY_PLANE;
                            break;
                        case 2:
                            r_plane = RPlane::YZ_PLANE;
                            break;
                        case 3:
                            r_plane = RPlane::XZ_PLANE;
                            break;
                        default:
                            continue;
                    }
                    //transform_m = matriz_cw * Matrix::reflection(r_plane) * matriz_wc;
                    transform_m = Matrix::reflection(r_plane);
                    break;
                case 6:
                    std::cout << "Type the new view port distance: " << std::endl<< ">> ";
                    std::cin >> dJanela;
                    zj = -dJanela;
                    obj_transformed = false;
                    
                    // scene.take_a_picture(camera, vp, bgColor);
                    break;
                case 7:
                    std::cout << "Type the new projection: " << std::endl;
                    std::cout << "1 - orthografic: " << std::endl;
                    std::cout << "2 - Perspective: " << std::endl<< ">> ";
                    std::cin >> index_;
                    switch (index_) {
                        case 1:
                            projection_type = Projection::ORTHOGRAPHIC;
                            break;
                        case 2:
                            projection_type = Projection::PERSPECTIVE;
                            break;
                        default:
                            continue;
                    }
                    scene.set_projection(projection_type);
                    obj_transformed = false;
                    break;
                case 8:
                    std::cout << "Type the new view port width: " << std::endl<< ">> ";
                    std::cin >> wJanela;
                    std::cout << "Type the new view port hight: " << std::endl<< ">> ";
                    std::cin >> hJanela;
                    obj_transformed = false;
                    
                    
                    // scene.take_a_picture(camera, vp, bgColor);
                    break;
                case 9:
                    std::cout << "1 - Set Ambient " << std::endl;
                    std::cout << "2 - Set Diffuse " << std::endl;
                    std::cout << "3 - Set Specular " << std::endl;
                    std::cout << "4 - Set Shineness " << std::endl<< ">> ";
                    std::cin >> index_;
                    if (index_ != 4) {
                        std::cout << "Digite a propriedade: " << std::endl<< ">> ";
                        std::cin >> x;
                        std::cin >> y;
                        std::cin >> z;
                        new_property = Vector3d(x, y, z);
                    }
                    
                    switch (index_) {
                        case 1:
                            pick_shape->set_ka(new_property);
                            break;
                        case 2:
                            pick_shape->set_kd(new_property);
                            break;
                        case 3:
                            pick_shape->set_ke(new_property);
                            break;
                        case 4:
                            std::cout << "Set shineness value: " << std::endl<< ">> ";
                            std::cin >> m;
                            pick_shape->set_m(m);
                            break;
                        default:
                            continue;
                    }
                    break;
                case 10:
                    std::cout << "Escolha uma fonte de luz: " << std::endl;

                    light_index = 0;
                    std::for_each(begin(lights), end(lights), [&light_index, &matriz_cw](Light *light_source){
                        std::cout << std::to_string(light_index) << " " << light_source->toStr(matriz_cw) << std::endl; 
                        light_index++;
                    });
                    std::cout << ">> ";
                    std::cin >> light_index;
                    lights.at(light_index)->change_some_proprety(matriz_wc);

                    break;
                case 11:

                    std::cout << "1 - modify eye position: |" << eye.mult_vector_matriz4d(matriz_cw.transform_matrix).toStr()<< std::endl;
                    std::cout << "2 - modify look at point: |" << at.toStr() << std::endl;
                    std::cout << "3 - modify view up point: |" << up.toStr() << std::endl << ">> ";
                    std::cin >> index_;

                    std::cout << "Set values x, y, z:" << std::endl<< ">> ";
                    std::cin >> x;
                    std::cin >> y;
                    std::cin >> z;
                    
                    eye * matriz_cw.transform_matrix;
                    if (index_ == 1){
                        eye = Vector3d(x, y, z);
                    }   
                    if (index_ == 2)
                        at = Vector3d(x, y, z);
                    if (index_ == 3)
                        up = Vector3d(x, y, z);

                    temp = matriz_cw;  
                    
                    matriz_wc = Matrix::world_camera(eye, at, up);
                    matriz_cw = Matrix::camera_world(eye, at, up);

                    eye * matriz_wc.transform_matrix;
                    camera = eye;

                    scene.update_world_camera(temp, matriz_wc);
                    
                    break;
                case 12:
                    std::cout << "#TODO" << std::endl;
                    //return EXIT_SUCCESS;
                default:
                    break;

                
            }
            if (pick_shape != nullptr && obj_transformed) {
                *pick_shape * transform_m; 
                std::cout << "after take a pic" << pick_shape->shape_center.toStr() << std::endl;
            }


            vp = ViewPort(wJanela, hJanela, zj); 
            dx = vp.width / (long double) canvas.n_cols();
            dy = vp.height / (long double) canvas.n_rows();

            std::cout << "Updating Scene... " << std::endl;
            scene.take_a_picture(camera, vp, bgColor);
            canvas.update_window();
            
        }
    });

    canvas.wait_event(&pick_shape, scene, camera, dx, dy, dJanela, vp, &clicked_point);
    return EXIT_SUCCESS;
}