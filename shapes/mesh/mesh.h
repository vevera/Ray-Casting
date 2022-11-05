#ifndef MESH_H
#define MESH_H

#include <set>

#include "../shape.h"
struct Edge {
    int id;
    int v1_id;
    int v2_id;

    Edge(int id_a, int v1, int v2) {
        id = id_a;
        v1_id = v1;
        v2_id = v2;
    }
};

struct Face {
    int id;
    int edge1_id;
    int edge2_id;
    int edge3_id;
    int normal_id;

    Face(int id_f, int ed1, int ed2, int ed3, int id_normal) {
        id = id_f;
        edge1_id = ed1;
        edge2_id = ed2;
        edge3_id = ed3;
        normal_id = id_normal;
    }
};

class Mesh : public Shape {
   public:
    Mesh(Reflexivity reflexivity, std::string object_data_pat,
         std::string texture_path = "");
    double intersect(Vector4d &p_0, Vector4d &dr);
    Vector4d normal(Vector4d &p_i);

    void operator*(AccMatrix m);
    void operator*(gMatrix m);

   private:
    std::vector<Vector4d> vertex_list = {Vector4d(0, 0, 0, 1)};
    std::vector<Vector4d> normal_list = {Vector4d(0, 0, 0, 0)};
    std::vector<Edge> edge_list = {Edge(0, 0, 0)};
    std::vector<Face> face_list = {Face(0, 0, 0, 0, 0)};
    void read_obj(std::string obj_path);
    void read_mtl(std::string mtl_path);
    Vector4d n;
    std::vector<Face *> back_face_culling(Vector4d dr);
};

#endif