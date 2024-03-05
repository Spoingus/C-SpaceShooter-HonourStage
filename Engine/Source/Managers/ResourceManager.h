#pragma once
#include <map>
#include <string>
#include <glad/glad.h>
#include "../Assets/Model.h"

namespace resource_manager
{
    //Maps for each resource loaded into the game
    static std::map<std::string, Model> model_map;
    static std::map<std::string, Texture> texture_map;
    static std::map<std::string, unsigned int> shader_map;

    //Memory Cleanup
    void remove_all_assets();
    
    //Model Loading Methods
    Mesh processMesh(aiMesh *mesh, const aiScene *scene, const std::string &directory);
    bool model_loaded(const std::string &directory);
    void model_to_map(Model *model, const std::string& directory);
    std::vector<Mesh> get_existing_meshes(const std::string& directory);

    //Texture Loading Methods
    std::vector<Texture> load_material_textures(const aiMaterial *mat, aiTextureType type, const std::string& type_name, const std::string& directory);
    unsigned int texture_from_file(const char *path, const std::string &directory);

    //Shader Loading Methods
    unsigned int load_shader(const std::string& shader_path, GLenum shader_type);
    void shader_compile_errors(unsigned int shader, std::string type);
}
