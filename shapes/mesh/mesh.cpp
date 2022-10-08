#include "mesh.h"
#include <fstream>
#include <regex>
#include <iostream>
#include <cstdio>

Mesh::Mesh(Reflexivity reflexivity, std::string object_data_path) : Shape(reflexivity)

{

    read_obj(object_data_path);
    read_mtl(object_data_path);
}

void Mesh::read_obj(std::string obj_path)
{

    std::regex vertex_regex("v\\s([-]?[0-9]+[\\.][0-9]+[\\s]?){3}");
    std::regex normals_regex("vn\\s([-]?[0-9]+[\\.][0-9]+[\\s]?){3}");
    std::regex faces_regex("f\\s([0-9]+/[0-9]+/[0-9]+[\\s]?){3}");

    std::ifstream obj_file(obj_path);
    std::string line;

    int id_edge = 1;
    int id_face = 1;

    if (obj_file.is_open())
    {
        while (obj_file)
        {
            std::getline(obj_file, line);
            if (regex_match(line, vertex_regex))
            {
                double x, y, z;
                sscanf(line.c_str(), "v %lf %lf %lf", &x, &z, &y);
                Vector3d vertex(x, y, z);
                vertex_list.push_back(vertex);
            }

            if (regex_match(line, normals_regex))
            {
                double x, y, z;
                sscanf(line.c_str(), "vn %lf %lf %lf", &x, &z, &y);
                Vector3d normal(x, y, z);
                normal_list.push_back(normal);
            }
            if (regex_match(line, faces_regex))
            {
                int v1, v2, v3, vt, n;
                sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt, &n, &v2, &vt, &n, &v3, &vt, &n);

                Edge edge_1(id_edge++, v1, v2);
                Edge edge_2(id_edge++, v2, v3);
                Edge edge_3(id_edge++, v3, v1);

                edge_list.insert(edge_list.end(), {edge_1, edge_2, edge_3});

                Face face(id_face++, edge_1.id, edge_2.id, edge_3.id, n);

                face_list.push_back(face);
            }
        }

        // std::for_each(begin(face_list), end(face_list), [](auto face)
        //               { std::cout << face.id << " " << face.edge1_id << " " << face.edge2_id << " " << face.edge3_id << " " << face.normal_id << std::endl; });

        // for (int i = 1; i < edge_list.size(); i++)
        // {

        //     std::cout << edge_list.get(i).id << " " << edge_list.at(i).v1_id << " " << edge_list.at(i).v2_id << std::endl;
        // }
    }
}

void Mesh::read_mtl(std::string mtl_path)
{
    return;
}

std::vector<Face> Mesh::back_face_culling(Vector3d dr)
{

    std::vector<Face> valid_faces;
    Vector3d n;

    std::for_each(begin(face_list) + 1, end(face_list), [&](Face face)
                  {
                      n = normal_list.at(face.normal_id);
                      if (n.dot(dr) < 0)
                      {
                          valid_faces.push_back(face);
                      } });

    return valid_faces;
}

double Mesh::intersect(Vector3d p_0, Vector3d dr)
{
    Vector3d r1, r2, p1, p2, p3, normal, p_i;
    double t_min = INFINITY;
    double c1, c2, c3, ti, min;
    bool it = true;

    auto valid_faces = back_face_culling(dr);
    std::for_each(begin(valid_faces), end(valid_faces), [&](Face face)
                  {
                      // std::cout << __LINE__ << std::endl;
                      p1 = vertex_list.at(edge_list.at(face.edge1_id).v2_id);
                      // std::cout << __LINE__ << "id: " << edge_list.at(face.edge1_id).v2_id <<  "p1: "<< p1.toStr() << std::endl;
                      p2 = vertex_list.at(edge_list.at(face.edge2_id).v2_id);
                      // std::cout << __LINE__ << "id: " << edge_list.at(face.edge2_id).v2_id << "p2: "<< p2.toStr() << std::endl;
                      p3 = vertex_list.at(edge_list.at(face.edge3_id).v2_id);
                      // std::cout << __LINE__ << "id: " << edge_list.at(face.edge3_id).v2_id << "p3: "<< p3.toStr() << std::endl;
                      r1 = p2 - p1;
                      r2 = p3 - p1;
                      //   std::cout<< __LINE__ << "r1: " << r1.toStr() << std::endl;
                      //   std::cout<< __LINE__ << "r2: " << r2.toStr() << std::endl;
                      // std::cout << "id: " << face.normal_id << std::endl;
                      normal = normal_list.at(face.normal_id);
                      //   std::cout << "normal: " << normal.toStr() << std::endl;
                      //   std::cout << "p0: " << p_0.toStr() << std::endl;
                      //   std::cout << "dr: " << dr.toStr() << std::endl;
                      // std::cout << __LINE__ << std::endl;
                      // std::cout <<  p1.toStr() << " : " << normal.toStr() << std::endl;
                      ti = -(p_0 - p1).dot(normal) / dr.dot(normal);
                      //   std::cout << "dn: " << -((p_0 - p1).dot(normal)) << std::endl;
                      //   std::cout << "nu: " << dr.dot(normal) << std::endl;
                      //   std::cout << "ti: " << ti << std::endl;
                      p_i = p_0 + (dr * ti);
                      //   std::cout << "pi: " << p_i.toStr() << std::endl;
                      //   std::cout << "p3 - pi: "<< (p3 - p_i).toStr() << std::endl;
                      //   std::cout << "p1 - pi: "<< (p1 - p_i).toStr() << std::endl;
                      //   std::cout << "p2 - pi: "<< (p2 - p_i).toStr() << std::endl;
                      c1 = ((p3 - p_i).cross_product(p1 - p_i).dot(normal) / r1.cross_product(r2).dot(normal));
                      c2 = ((p1 - p_i).cross_product(p2 - p_i).dot(normal) / r1.cross_product(r2).dot(normal));
                      c3 = 1 - c1 - c2;

                      //   std::cout << "c1: " << c1 << std::endl;
                      //   std::cout << "c2: " << c2 << std::endl;
                      //   std::cout << "c3: " << c3 << std::endl;

                      min = std::min({c1, c2, c3});
                      //std::cout << "min: " << min << std::endl;
                      if (min >= 0)
                      {
                          //std::cout << "DENTRO DO IF: " << std::endl;
                          t_min = ti  < t_min ? ti  : t_min;
                          n = &normal;
                      } });
    if (t_min != INFINITY && t_min >= 0)
    {
        // std::cout << t_min << std::endl;
    }
    // std::cout << "t_min: " << t_min << std::endl;
    return t_min;
}
Vector3d Mesh::normal(Vector3d p_i)
{
    return *n;
}