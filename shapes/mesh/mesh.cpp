#include "mesh.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>

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
                Vector4d vertex(x, y, z, 1);
                vertex_list.push_back(vertex);
            }

            if (regex_match(line, normals_regex)) {
                double x, y, z;
                sscanf(line.c_str(), "vn %lf %lf %lf", &x, &z, &y);
                Vector4d normal(x, y, z, 0);
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

std::vector<Face *> Mesh::back_face_culling(Vector4d dr) {
    std::vector<Face *> valid_faces;
    Vector4d n;

    std::for_each(begin(face_list) + 1, end(face_list), [&](Face &face) {
        n = normal_list.at(face.normal_id);
        if (n.dot(dr) < 0) {
            valid_faces.push_back(&face);
        }
    });

    return valid_faces;
}

double Mesh::intersect(Vector4d &p_0, Vector4d &dr) {
    Vector4d r1, r2, p1, p2, p3, normal, p_i;
    double t_min = INFINITY;
    double c1, c2, c3, ti, min;
    bool it = true;

    auto valid_faces = back_face_culling(dr);

    std::for_each(begin(valid_faces), end(valid_faces), [&](Face *face) {
        p1 = vertex_list.at(edge_list.at(face->edge1_id).v2_id);
        p2 = vertex_list.at(edge_list.at(face->edge2_id).v2_id);
        p3 = vertex_list.at(edge_list.at(face->edge3_id).v2_id);

        r1 = p2 - p1;
        r2 = p3 - p1;

        normal = normal_list.at(face->normal_id);
        ti = -(p_0 - p1).dot(normal) / dr.dot(normal);
        p_i = p_0 + (dr * ti);

        c1 = ((p3 - p_i)
                  .head<3>()
                  .cross((p1 - p_i).head<3>())
                  .dot(normal.head<3>()) /
              r1.head<3>().cross(r2.head<3>()).dot(normal.head<3>()));
        c2 = ((p1 - p_i)
                  .head<3>()
                  .cross((p2 - p_i).head<3>())
                  .dot(normal.head<3>()) /
              r1.head<3>().cross(r2.head<3>()).dot(normal.head<3>()));
        c3 = 1 - c1 - c2;

        min = std::min({c1, c2, c3});
        if (min >= 0.0) {
            if (ti < t_min) {
                t_min = ti;
                n = normal;
            }
        }
    });

    return t_min;
}
Vector4d Mesh::normal(Vector4d &p_i) { return n; }

void Mesh::operator*(AccMatrix m) {
    std::for_each(m.acc->begin(), m.acc->end(), [&](gMatrix &m) { *this *m; });
};

void Mesh::operator*(gMatrix m) {
    std::for_each(begin(vertex_list) + 1, end(vertex_list),
                  [&](Vector4d &p) { p = m.transform_matrix * p; });

    std::for_each(begin(normal_list) + 1, end(normal_list), [&](Vector4d &p) {
        p = (m.n_fix * p).normalized();
        // p.set(3, 0);
    });

    // if (m.t_type == TransformType::CAMERA) {
    //     std::for_each(
    //         begin(normal_list) + 1, end(normal_list), [&](Vector3d &p) {
    //             p = p.mult_vector_matriz4d(m.transform_matrix).normalize();
    //             p.set(3, 0);
    //         });
    // } else {
    //     std::for_each(begin(normal_list) + 1, end(normal_list),
    //                   [&](Vector3d &p) {
    //                       p = p.mult_vector_matriz4d(m.n_fix).normalize();
    //                       p.set(3, 0);
    //                   });
    // }

    // switch (m.t_type) {
    //     case TransformType::SHEARING:
    //         std::for_each(
    //             begin(normal_list) + 1, end(normal_list), [&](Vector3d &p) {
    //                 p =
    //                 p.mult_vector_matriz4d(m.transform_matrix).normalize();
    //             });
    //         break;
    //     case TransformType::CAMERA:
    //         std::for_each(
    //             begin(normal_list) + 1, end(normal_list), [&](Vector3d &p) {
    //                 p =
    //                 p.mult_vector_matriz4d(m.transform_matrix).normalize();
    //             });
    //         break;
    //     // case TR:
    //     //     std::for_each(
    //     //         begin(normal_list) + 1, end(normal_list), [&](Vector3d &p)
    //     {
    //     //             p =
    //     p.mult_vector_matriz(m.transform_matrix).normalize();
    //     //         });
    //     //     break;
    //     default:
    //         std::for_each(
    //             begin(normal_list) + 1, end(normal_list), [&](Vector3d &p) {
    //                 p = p.mult_vector_matriz(m.transform_matrix).normalize();
    //             });
    //         break;
    // }
};