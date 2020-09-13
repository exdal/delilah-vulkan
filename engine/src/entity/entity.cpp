#include "entity.h"
#include <algorithm>

Entity *entity::create(Scene *scene) {
    auto entity = new (Entity);
    entity->scene = scene;
    entity->handle = scene->registry.create();
    return entity;
}

void entity::sort_by_depth(std::vector<Entity *> vec){ 
    /*std::sort(vec.begin(), vec.end(), [](Entity *left, Entity *right) { 
        float f1 = get_component<TransformComponent>(left).z_index;
        float f2 = get_component<TransformComponent>(right).z_index;
        return f1 < f2; 
        });*/
}

/*Entity *entity::create_text(Scene *scene, Font *font, const std::string &text, const glm::vec3 &position, const glm::vec4 &color) {
    auto entity = entity::create(scene);

    TransformComponent transform;
    transform.size = glm::vec2(1, 1);
    transform.position = { position.x, position.y };
    transform.z_index = position.z;
    transform.rotation = 0;

    entity::add_component<TransformComponent>(entity, transform);
    entity::add_component<ColorComponent>(entity, color);
    entity::add_component<TextComponent>(entity, font, text);
    scene->text_entities.push_back(entity);

    return entity;
}

Entity *entity::create_rect(Scene *scene, const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
    auto entity = entity::create(scene);

    TransformComponent transform;
    transform.size = size;
    transform.position = { position.x, position.y };
    transform.z_index = position.z;
    transform.rotation = 0;

    entity::add_component<TransformComponent>(entity, transform);
    entity::add_component<ColorComponent>(entity, color);
    scene->entities.push_back(entity);

    return entity;
}

Entity *entity::create_rect(Scene *scene, Texture *texture, TransformComponent transform, ColorComponent color) {
    auto entity = entity::create(scene);
    /*entity::add_component<TransformComponent>(entity, transform);
    entity::add_component<ColorComponent>(entity, color);
    entity::add_component<TextureComponent>(entity, texture);
    scene->entities.push_back(entity);

    return entity;
}
*/