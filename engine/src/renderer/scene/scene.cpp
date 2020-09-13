#include "scene.h"
#include <renderer/renderer.h>
#include <entity/entity.h>
#include <game/game.h>

void scene::render(Scene *scene) {
    renderer::new_frame();
    /*renderer::bind_framebuffer(game::get()->main_framebuffer, GL_ONE);
    for (auto &ent : scene->text_entities) {
        if (entity::has_component<TextComponent>(ent)) {
            TextComponent textc = entity::get_component<TextComponent>(ent);
            TransformComponent transc = entity::get_component<TransformComponent>(ent);

            renderer::draw_text(textc.font, textc.text, { transc.position.x, transc.position.y, transc.z_index }, { 1, 1 }, entity::get_component<ColorComponent>(ent));
        }
    }
    renderer::unbind_framebuffer();*/
    renderer::end_frame();

    renderer::new_frame();
    /*renderer::bind_framebuffer(game::get()->main_framebuffer, GL_SRC_ALPHA);
    for (auto &ent : scene->entities) {
        if (entity::has_component<TransformComponent>(ent) && entity::has_component<ColorComponent>(ent)) {
            TransformComponent transc = entity::get_component<TransformComponent>(ent);
            ColorComponent colorc = entity::get_component<ColorComponent>(ent);
            renderer::draw_quad({ transc.position.x, transc.position.y, transc.z_index }, transc.size, entity::get_component<ColorComponent>(ent));
        }
    }
    renderer::unbind_framebuffer();*/
    renderer::end_frame();
}