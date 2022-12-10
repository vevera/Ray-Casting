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
    double dJanela, zj;
    Vector3d bgColor, i_f, p_f, p_f2, i_a;
    wCanvas = 500;
    hCanvas = 500;
    dJanela = 25;
    rEsfera = 40;
    wJanela = 70;
    hJanela = 70;
    bgColor = Vector3d(0., 0., 0.);
    nLin = 500;
    nCol = 500;
    zj = -dJanela;

    i_f = Vector3d(0.7, 0.7, 0.7);
    p_f = Vector3d(1750, 500, 6000.0);
    // p_f2 = Vector3d(300, 8000, 500.0);
    i_a = Vector3d(0.3, 0.3, 0.3);

    // lights.push_back(&d_light);
    // lights.push_back(&s_light);
    // lights.push_back(&s1_light);
    std::vector<Shape *> shapes;

    // Posicao do fotografo -------------------------------- begin
    /*
    int lx =
    */
    double lx = 1750;
    double ly = 500;
    double lz = 6000;

    Vector3d camera(0, 0, 0);
    Vector3d eye = Vector3d(lx, ly, lz, 1);

    Vector3d at = Vector3d(1750, 500, 3000, 1);

    Vector3d up = Vector3d(lx, ly + 100, lz, 1);

    gMatrix matriz_wc = Matrix::world_camera(eye, at, up);
    gMatrix matriz_cw = Matrix::camera_world(eye, at, up);

    eye * matriz_wc.transform_matrix;
    camera = eye;

    std::vector<Light *> lights;

    PointLight light(i_f, p_f, "Luz Pontual 1");

    Ambient ambient_light(i_a, "Luz Ambiente 1");

    lights.push_back(&light);
    lights.push_back(&ambient_light);


    /**
    
    
    

    
    */
    // START OF FINAL SCENE

    Vector3d k_support_table =
        Vector3d(210.0 / 255.0, 105.0 / 255.0, 30.0 / 255.0);
    Reflexivity reflex_support_table(k_support_table, k_support_table,
                                     k_support_table, 1);

    /*---------------------------------------------------------------------------------*/

    Mesh left_church_front(reflex_support_table, "blender objects/cubo_17.obj");
    auto scale_side_church = Matrix::scale(Vector3d(1000, 1800, 10));
    auto t_left_church = scale_side_church * Matrix::translate(Vector3d(500, 900, 3005));

    left_church_front * t_left_church;

    Mesh left_church_back = left_church_front;
    left_church_back * Matrix::translate(Vector3d(0, 0, -3000));

    /*---------------------------------------------------------------------------------*/

    Mesh left_church_left(reflex_support_table, "blender objects/cubo_17.obj");
    auto scale_side_church_left = Matrix::scale(Vector3d(10, 1800, 3000));
    auto t_left_church_left = scale_side_church_left * Matrix::translate(Vector3d(5, 900, 1500));

    left_church_left * t_left_church_left;

    Mesh left_church_right = left_church_left;
    left_church_right * Matrix::translate(Vector3d(1000, 0, 0));


    /*---------------------------------------------------------------------------------*/

    Mesh right_church_front = left_church_front;
    right_church_front * Matrix::translate(Vector3d(2500, 0, 0));

    Mesh right_church_back = right_church_front;
    right_church_back * Matrix::translate(Vector3d(0, 0, -3000));

    /*---------------------------------------------------------------------------------*/

    Mesh right_church_left = left_church_left;
    right_church_left * Matrix::translate(Vector3d(2500, 0, 0));

    Mesh right_church_right = right_church_left;
    right_church_right * Matrix::translate(Vector3d(1000, 0, 0));

    /*--------------------------CENTER CHURCH------------------------------------------*/
    /*---------------------------------------------------------------------------------*/

    Mesh center_church_front(reflex_support_table, "blender objects/cubo_17.obj");

    center_church_front * ( Matrix::scale(Vector3d(1500, 3000, 10)) * Matrix::translate(Vector3d(1750, 1500, 3105)));

    Mesh center_church_back = center_church_front;
    center_church_back * Matrix::translate(Vector3d(0, 0, -3100));

    /*---------------------------------------------------------------------------------*/

    // Mesh center_church_left = left_church_left;
    // center_church_left * Matrix::translate(Vector3d(2500, 0, 0));

    // Mesh center_church_right = center_church_left;
    // center_church_right * Matrix::translate(Vector3d(1000, 0, 0));


    // END OF FINAL SCENE
    /**
    
    
    
    
    
    */


    // Reflexidade dos objetos
    Vector3d k_spec = Vector3d(0, 0, 0);
    Vector3d k_floor_a = Vector3d(0.3, 0.6, 0.1);
    Reflexivity reflex_floor(k_floor_a, k_floor_a, k_floor_a, 1);

    // Vector3d k_support_table =
    //     Vector3d(210.0 / 255.0, 105.0 / 255.0, 30.0 / 255.0);
    // Reflexivity reflex_support_table(k_support_table, k_support_table,
    //                                  k_support_table, 1);

    Vector3d k_lid_table = Vector3d(65.0 / 255.0, 105.0 / 255.0, 225.0 / 255.0);
    Reflexivity reflex_lid_table(k_lid_table, k_lid_table, k_lid_table, 1);

    Vector3d k_tree_wood = Vector3d(139.0 / 255.0, 69.0 / 255.0, 19.0 / 255.0);
    Reflexivity reflex_tree_wood(k_tree_wood, k_tree_wood, k_tree_wood, 1);

    Vector3d k_tree_support = Vector3d(1, 1, 0);

    Reflexivity reflex_support(k_tree_support, k_tree_support,
                               k_tree_support, 1);

    Vector3d k_star = Vector3d(1.0, 1.0, 0.0);
    Reflexivity reflex_star(k_star, k_star, k_star, 1);

    Vector3d k_tree = Vector3d(0.0, 1.0, 0.0);
    Reflexivity reflex_tree(k_tree, k_tree, k_tree, 1);

    Vector3d k_wood_column =
        Vector3d(205.0 / 255.0, 133.0 / 255.0, 63.0 / 255.0);
    Reflexivity reflex_wood_column(k_wood_column, k_wood_column,
                                   k_wood_column, 1);

    Vector3d k_roof = Vector3d(1, 69.0 / 255.0, 0);
    Reflexivity reflex_roof(k_roof, k_roof, k_roof, 1);

    Vector3d k_wall = Vector3d(222.0 / 255.0, 184.0 / 255.0, 135.0 / 255.0);
    Reflexivity reflex_wall(k_wall, k_wall, k_wall, 1);

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

    Sphere cat_wrap(reflex_star, Vector3d(0, 0, 0), 2);

    Mesh gato(reflex_wood_column, "blender objects/gato_1.obj", &cat_wrap); 
    gato *(Matrix::scale(Vector3d(250, 250, 250)) *
           Matrix::translate(Vector3d(300, 0, 600)));
    //gato *matriz_wc;

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

    Mesh left_beam(reflex_wood_column, "blender objects/cubo_17.obj");
    auto left_beam_t = Matrix::scale(Vector3d(300, 50, 30)) *
                       Matrix::translate(Vector3d(150.0, 600.0, 1000.0));
                       
    left_beam *left_beam_t;

    Mesh right_beam = left_beam;
    auto right_beam_t = Matrix::translate(Vector3d(-150, -600, -1000)) *
                        Matrix::reflection(RPlane::YZ_PLANE) *
                        Matrix::translate(Vector3d(450, 600, 1000));

    right_beam *(right_beam_t);

    Mesh back_left_beam(reflex_wood_column, "blender objects/cubo_17.obj");
    auto back_left_beam_t = 
                            Matrix::scale(Vector3d(300, 50, 30)) *
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

    left_roof *left_roof_t;

    Mesh right_roof = left_roof;
    auto right_roof_t = Matrix::translate(Vector3d(-150, -600, -1000)) *
                        Matrix::reflection(RPlane::YZ_PLANE) *
                        Matrix::translate(Vector3d(450, 600, 1000));

    right_roof *(right_roof_t);

    Mesh left_wall(reflex_wall, "blender objects/cubo_17.obj");
    auto left_wall_t = Matrix::scale(Vector3d(20, 500, 1000)) *
                       Matrix::translate(Vector3d(0, 250, 500));

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
    //LEFT CHURCH
    shapes.push_back(&left_church_front);
    shapes.push_back(&left_church_back);
    shapes.push_back(&left_church_left);
    shapes.push_back(&left_church_right);
    //RIGHT CHURCH
    shapes.push_back(&right_church_front);
    shapes.push_back(&right_church_back);
    shapes.push_back(&right_church_left);
    shapes.push_back(&right_church_right);
    //CENTER CHURCH
    shapes.push_back(&center_church_front);
    shapes.push_back(&center_church_back);
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

    double dx = vp.width / (double) canvas.n_cols();
    double dy = vp.height / (double) canvas.n_rows();

    std::thread object_operations([&]() {

        int option, index_, light_index;
        double x, y, z, angle, angle_shear, m;
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
                    transform_m = Matrix::translate(pick_shape->shape_center * -1) * Matrix::rotate(axis, angle) * Matrix::translate(pick_shape->shape_center);
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
                    transform_m = matriz_cw * Matrix::reflection(r_plane) * matriz_wc;
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
                std::cout << "after take a pic" << std::endl;
            }


            vp = ViewPort(wJanela, hJanela, zj); 
            dx = vp.width / (double) canvas.n_cols();
            dy = vp.height / (double) canvas.n_rows();

            std::cout << "Updating Scene... " << std::endl;
            scene.take_a_picture(camera, vp, bgColor);
            canvas.update_window();
            
        }
    });

    canvas.wait_event(&pick_shape, scene, camera, dx, dy, dJanela, vp, &clicked_point);
    return EXIT_SUCCESS;
}