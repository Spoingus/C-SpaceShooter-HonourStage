#ifndef MODEL_H
#define MODEL_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <../../Engine/Source/Assets/Mesh.h>
#include <../../Engine/Source/Assets/Shader.h>
#include <string>
#include <vector>

class Model
{
public:
    
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gamma_correction;

    Model(std::string const &path, bool gamma = false);
    
    void Draw(const Shader &shader) const;

private:
    
    void loadModel(std::string const &path);
    void processNode(const aiNode *node, const aiScene *scene);
};
#endif
