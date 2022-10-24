#include "mesh.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>

int d = 1;

Mesh::Mesh(Reflexivity reflexivity, std::string object_data_path,
           std::string texture_path)
    : Shape(reflexivity, texture_path)

{
    read_obj(object_data_path);
    read_mtl(object_data_path);
}

void Mesh::read_obj(std::string obj_path) {
    std::regex vertex_regex("v\\s([-]?[0-9]+[\\.][0-9]+[\\s]?){3}");
    std::regex normals_regex("vn\\s([-]?[0-9]+[\\.][0-9]+[\\s]?){3}");
    std::regex faces_regex("f\\s([0-9]+/[0-9]+/[0-9]+[\\s]?){3}");

    std::ifstream obj_file(obj_path);
    std::string line;

    int id_edge = 1;
    int id_face = 1;

    if (obj_file.is_open()) {
        while (obj_file) {
            std::getline(obj_file, line);
            if (regex_match(line, vertex_regex)) {
                double x, y, z;
                sscanf(line.c_str(), "v %lf %lf %lf", &x, &z, &y);
                Vector3d vertex(x, y, z);
                vertex_list.push_back(vertex);
            }

            if (regex_match(line, normals_regex)) {
                double x, y, z;
                sscanf(line.c_str(), "vn %lf %lf %lf", &x, &z, &y);
                Vector3d normal(x, y, z);
                normal_list.push_back(normal);
            }
            if (regex_match(line, faces_regex)) {
                int v1, v2, v3, vt, n;
                sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt,
                       &n, &v2, &vt, &n, &v3, &vt, &n);

                Edge edge_1(id_edge++, v1, v2);
                Edge edge_2(id_edge++, v2, v3);
                Edge edge_3(id_edge++, v3, v1);

                edge_list.insert(edge_list.end(), {edge_1, edge_2, edge_3});

                Face face(id_face++, edge_1.id, edge_2.id, edge_3.id, n);

                face_list.push_back(face);
            }
        }
    }
}

void Mesh::read_mtl(std::string mtl_path) { return; }

std::vector<Face> Mesh::back_face_culling(Vector3d dr) {
    std::vector<Face> valid_faces;
    Vector3d n;

    std::for_each(begin(face_list) + 1, end(face_list), [&](Face face) {
        n = normal_list.at(face.normal_id);
        if (n.dot(dr) < 0) {
            valid_faces.push_back(face);
        }
    });

    return valid_faces;
}

double Mesh::intersect(Vector3d p_0, Vector3d dr) {
    Vector3d r1, r2, p1, p2, p3, normal, p_i;
    double t_min = INFINITY;
    double c1, c2, c3, ti, min;
    bool it = true;

    auto valid_faces = back_face_culling(dr);

    std::for_each(begin(valid_faces), end(valid_faces), [&](Face face) {
        p1 = vertex_list.at(edge_list.at(face.edge1_id).v2_id);
        p2 = vertex_list.at(edge_list.at(face.edge2_id).v2_id);
        p3 = vertex_list.at(edge_list.at(face.edge3_id).v2_id);

        r1 = p2 - p1;
        r2 = p3 - p1;

        normal = normal_list.at(face.normal_id);
        ti = -(p_0 - p1).dot(normal) / dr.dot(normal);
        p_i = p_0 + (dr * ti);

        if (d == 1) {
            std::cout << ti << std::endl;
            std::cout << p_i.toStr() << std::endl;
        }

        c1 = ((p3 - p_i).cross_product(p1 - p_i).dot(normal) /
              r1.cross_product(r2).dot(normal));
        c2 = ((p1 - p_i).cross_product(p2 - p_i).dot(normal) /
              r1.cross_product(r2).dot(normal));
        c3 = 1 - c1 - c2;

        if (d == 1) {
            std::cout << c1 << std::endl;
            std::cout << c2 << std::endl;
            std::cout << c3 << std::endl;
        }
        min = std::min({c1, c2, c3});
        if (min >= 0.0) {
            if (ti < t_min) {
                t_min = ti;
                n = normal;
            }
        }

        d = d + 1;
    });

    return t_min;
}

Vector3d Mesh::normal(Vector3d p_i) { return n; }

void Mesh::scale(Vector3d scale_factor) {
    // FALTA ARRUMAR A NORMAL

    std::vector<Vector3d> matrix_scale = {
        Vector3d(scale_factor.x_, 0, 0, 0), Vector3d(0, scale_factor.y_, 0, 0),
        Vector3d(0, 0, scale_factor.z_, 0), Vector3d(0, 0, 0, 1)};

    std::vector<Vector3d> inverse_m = {Vector3d(1 / scale_factor.x_, 0, 0, 0),
                                       Vector3d(0, 1 / scale_factor.y_, 0, 0),
                                       Vector3d(0, 0, 1 / scale_factor.z_, 0),
                                       Vector3d(0, 0, 0, 1)};

    std::for_each(begin(vertex_list) + 1, end(vertex_list), [&](Vector3d &p) {
        p = p.mult_vector_matriz4d(matrix_scale);
    });
    std::for_each(begin(normal_list) + 1, end(normal_list), [&](Vector3d &p) {
        p = p.mult_vector_matriz4d(inverse_m).normalize();
    });
}

void Mesh::translate(Vector3d target_position) {
    std::vector<Vector3d> matrix_scale = {Vector3d(1, 0, 0, target_position.x_),
                                          Vector3d(0, 1, 0, target_position.y_),
                                          Vector3d(0, 0, 1, target_position.z_),
                                          Vector3d(0, 0, 0, 1)};

    std::for_each(begin(vertex_list) + 1, end(vertex_list), [&](Vector3d &p) {
        p = p.mult_vector_matriz4d(matrix_scale);
    });
}

void Mesh::rotate(Axis rotation_axis, double angle) {
    angle = (angle * M_PI) / 180;

    std::vector<Vector3d> matrix_scale;

    double cos_t = cos(angle);
    double sin_t = sin(angle);

    switch (rotation_axis) {
        case Axis::X_AXIS:
            matrix_scale = {Vector3d(1, 0, 0, 0), Vector3d(0, cos_t, -sin_t, 0),
                            Vector3d(0, sin_t, cos_t, 0), Vector3d(0, 0, 0, 1)};
            break;
        case Axis::Y_AXIS:
            matrix_scale = {Vector3d(cos_t, 0, sin_t, 0), Vector3d(0, 1, 0, 0),
                            Vector3d(-sin_t, 0, cos_t, 0),
                            Vector3d(0, 0, 0, 1)};
            break;
        case Axis::Z_AXIS:
            matrix_scale = {Vector3d(cos_t, -sin_t, 0, 0),
                            Vector3d(sin_t, cos_t, 0, 0), Vector3d(0, 0, 1, 0),
                            Vector3d(0, 0, 0, 1)};
            break;
    }

    std::for_each(begin(vertex_list) + 1, end(vertex_list), [&](Vector3d &p) {
        p = p.mult_vector_matriz4d(matrix_scale);
    });

    std::for_each(begin(normal_list) + 1, end(normal_list), [&](Vector3d &p) {
        p = p.mult_vector_matriz4d(matrix_scale).normalize();
    });
}

void Mesh::shearing(ShearingTypes shearing_axis, double angle) {
    // FALTA ARRUMAR A NORMAL

    angle = (angle * M_PI) / 180;
    std::vector<Vector3d> matrix_scale;
    std::vector<Vector3d> inverse_t;

    double tg_t = tan(angle);

    switch (shearing_axis) {
        case ShearingTypes::XZ:
            matrix_scale = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                            Vector3d(tg_t, 0, 1, 0), Vector3d(0, 0, 0, 1)};

            inverse_t = {Vector3d(1, 0, -tg_t, 0), Vector3d(0, 1, 0, 0),
                         Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};

            break;
        case ShearingTypes::ZX:
            matrix_scale = {Vector3d(1, 0, tg_t, 0), Vector3d(0, 1, 0, 0),
                            Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};

            inverse_t = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                         Vector3d(-tg_t, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
        case ShearingTypes::YZ:
            matrix_scale = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                            Vector3d(0, tg_t, 1, 0), Vector3d(0, 0, 0, 1)};
            inverse_t = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, -tg_t, 0),
                         Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
        case ShearingTypes::ZY:
            matrix_scale = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, tg_t, 0),
                            Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            inverse_t = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                         Vector3d(0, -tg_t, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
        case ShearingTypes::XY:
            matrix_scale = {Vector3d(1, 0, 0, 0), Vector3d(tg_t, 1, 0, 0),
                            Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            inverse_t = {Vector3d(1, -tg_t, 0, 0), Vector3d(0, 1, 0, 0),
                         Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
        case ShearingTypes::YX:
            matrix_scale = {Vector3d(1, tg_t, 0, 0), Vector3d(0, 1, 0, 0),
                            Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            inverse_t = {Vector3d(1, 0, 0, 0), Vector3d(-tg_t, 1, 0, 0),
                         Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
    }

    std::for_each(begin(vertex_list) + 1, end(vertex_list), [&](Vector3d &p) {
        p = p.mult_vector_matriz4d(matrix_scale);
    });

    std::for_each(begin(normal_list) + 1, end(normal_list), [&](Vector3d &n) {
        n = n.mult_vector_matriz4d(inverse_t).normalize();
    });
}

void Mesh::reflection(ReflectionPlane r_plane) {
    std::vector<Vector3d> matrix_scale;

    switch (r_plane) {
        case ReflectionPlane::XY_PLANE:
            matrix_scale = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                            Vector3d(0, 0, -1, 0), Vector3d(0, 0, 0, 1)};
            break;
        case ReflectionPlane::YZ_PLANE:
            matrix_scale = {Vector3d(-1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                            Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
        case ReflectionPlane::XZ_PLANE:
            matrix_scale = {Vector3d(1, 0, 0, 0), Vector3d(0, -1, 0, 0),
                            Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
    }

    std::for_each(begin(vertex_list) + 1, end(vertex_list), [&](Vector3d &p) {
        p = p.mult_vector_matriz4d(matrix_scale);
    });

    std::for_each(begin(normal_list) + 1, end(normal_list), [&](Vector3d &p) {
        p = p.mult_vector_matriz4d(matrix_scale);
    });
}
