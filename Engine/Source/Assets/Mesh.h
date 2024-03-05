#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <../../Engine/Source/Assets/Shader.h>
#include <string>
#include <vector>

struct Vertex {
    glm::vec3 Position, Normal, Tangent, Bitangent;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};
class Mesh {
public:
    // mesh Data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;
    
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
    void Draw(const Shader &shader) const;

private:
    unsigned int VBO, EBO;

    void setup_mesh();
};
#endif