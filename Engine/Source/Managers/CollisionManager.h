#pragma once

class CollisionManager{
    CollisionManager() = default;
public:
    CollisionManager(const CollisionManager&) = delete;
    CollisionManager& operator=(const CollisionManager&) = delete;
    CollisionManager(CollisionManager&&) = delete;
    CollisionManager& operator=(CollisionManager&&) = delete;

    static bool check_terrain(float &velocity, const Model &terrain, const glm::vec3 &entity_position, const float &entity_radius);
    static bool check_spheres(const glm::vec3 &sphere_1_pos, float sphere_1_rad, const glm::vec3 &sphere_2_pos , float sphere_2_rad);
    static bool check_world_sphere(const glm::vec3& entity_pos, const float &entity_rad, const float &world_sphere_rad);

    static CollisionManager& get(){
        static CollisionManager instance;
        return instance;
    }
};
