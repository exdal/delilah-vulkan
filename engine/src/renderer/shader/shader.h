#pragma once
#include <glm/glm.hpp>
#include <string>

#define SHADER_UNIFORM Shader shader, const char *name

using Shader = uint32_t;

namespace shader {
    void compile(uint32_t shader, const char *data);
    Shader load(const char *vertex, const char *fragment);
    void use(Shader shader);
    int uniform(SHADER_UNIFORM);

    // type functions to make our job easier, atleast save one line
    void set_int_arr(SHADER_UNIFORM, int32_t *val, uint32_t size);
    void set_int(SHADER_UNIFORM, uint32_t val);
    void set_float(SHADER_UNIFORM, float val);
    void set_vec4(SHADER_UNIFORM, glm::vec4 val);
    void set_vec3(SHADER_UNIFORM, glm::vec3 val);
    void set_vec2(SHADER_UNIFORM, glm::vec2 val);
    void set_mat4(SHADER_UNIFORM, glm::mat4 matrix);
}