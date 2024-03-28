#include "pch.h"
#include "CollisionManager.h"

bool CollisionManager::check_terrain(float &velocity, const Model& terrain, const glm::vec3& entity_position, const float& entity_radius)
{
    Vertex nearest_vertex = terrain.meshes[0].vertices[0];
    float shortest_distance = 1000;
    for (auto vertex : terrain.meshes[0].vertices)
    {
        const float distance = glm::distance(vertex.position, entity_position);
        if (distance < shortest_distance)
        {shortest_distance = distance; nearest_vertex = vertex;}
    }
    float incline = nearest_vertex.position.y - (entity_position.y - entity_radius);
    if(incline > 0.6f)
        velocity*=-1;
    if (nearest_vertex.position.y > entity_position.y - entity_radius)
        return true;
        
    return false;
}

bool CollisionManager::check_spheres(const glm::vec3& sphere_1_pos, float sphere_1_rad, const glm::vec3& sphere_2_pos, float sphere_2_rad)
{
    if (glm::distance(sphere_1_pos, sphere_2_pos) < sphere_1_rad + sphere_2_rad)
        return true;
    return false;
}

bool CollisionManager::check_world_sphere(const glm::vec3& entity_pos, const float &entity_rad, const float &world_sphere_rad)
{
    if (glm::distance(glm::vec3(0,0,0), entity_pos) > entity_rad + world_sphere_rad)
        return true;
    return false;
}

