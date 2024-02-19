#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Texture
{
    unsigned int id;
    std::string image_name;
};
struct Material
{
    Texture diffuse;
    Texture normal;
    Texture specular;
};
struct Mesh
{
    std::vector<glm::vec3> position, normal, tangent, bi_tangent;
    std::vector<glm::vec2> tex_coords;
    std::vector<unsigned int> indices;
    // handles to vao, vbo and ebo
    unsigned int vao_handle, vbo_vertices, vbo_texture_coords, vbo_normals, ebo_handle;
    Material material;
    std::string directory;
};

class Geometry
{
public:
    unsigned int mesh_index;
    std::vector<Mesh> meshes;
    
    Geometry();
    Geometry(const std::string& filename) { LoadMesh(filename); }
    
    void LoadMesh(const std::string& filename);
    void Draw();

private:
    
    void setup_mesh(unsigned int i);
};
