#pragma once
#include <entt.hpp>
#include <renderer/renderer.h>
#include <renderer/scene/scene.h>

struct Entity {
    entt::entity handle{ entt::null };
    Scene *scene;
};

namespace entity {
    Entity *create(Scene *scene);

    template<typename T, typename... Args>
    T &add_component(Entity *entity, Args &&... args) { 
        return entity->scene->registry.emplace<T>(entity->handle, std::forward<Args>(args)...);
    }

    template<typename T>
    T &get_component(Entity *entity) {
        return entity->scene->registry.get<T>(entity->handle);
    }

    template <typename T>
    bool has_component(Entity *entity) {
        return entity->scene->registry.has<T>(entity->handle);
    }

    template <typename T>
    void remove_component(Entity *entity) {
        return entity->scene->registry.remove<T>(entity->handle);
    }

    void sort_by_depth(std::vector<Entity *> vec);

    /*Entity *create_text(Scene *scene, Font *font, const std::string &text, const glm::vec3 &position, const glm::vec4 &color = { 1, 1, 1, 1 });
    Entity *create_rect(Scene *scene, const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color = { 1, 1, 1, 1 });
    Entity *create_rect(Scene *scene, Texture *texture, TransformComponent transform, ColorComponent color = { { 1, 1, 1, 1 } });*/
    /*Entity *create_tile(Scene *scene, Texture *texture, glm::vec4 tex_coords, TransformComponent transform, ColorComponent color = { { 1, 1, 1, 1 } });
    Entity *create_tile_f(Scene *scene, Texture *texture, glm::vec4 tex_coords, TransformComponent transform, ColorComponent color = { { 1, 1, 1, 1 } });*/
}