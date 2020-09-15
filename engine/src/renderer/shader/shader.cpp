#include "shader.h"
#include <utils/logger.h>
#include <filesys/filesys.h>
#include <string>
#include <vector>

/*void shader::compile(GLuint shader, const char *data) {
    GLint result;
    int info_len;
    glShaderSource(shader, 1, &data, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);

    if (info_len > 0) {
        std::vector<char> msg(info_len + 1);
        glGetShaderInfoLog(shader, info_len, NULL, &msg[0]);
        logger::logf("%s\n", &msg[0]);
    }
}
*/
Shader shader::load(const char *vertex, const char *fragment) {

    return 0;
}
/*
void shader::use(Shader shader) {
    glUseProgram(shader);
}

int shader::uniform(SHADER_UNIFORM) {
    return glGetUniformLocation(shader, name);
}

void shader::set_int(SHADER_UNIFORM, uint32_t val) {
    auto uni = shader::uniform(shader, name);
    glUniform1i(uni, val);
}

void shader::set_int_arr(SHADER_UNIFORM, int32_t *val, uint32_t size) {
    auto uni = shader::uniform(shader, name);
    glUniform1iv(uni, size, val);
}

void shader::set_float(SHADER_UNIFORM, float val) {
    auto uni = shader::uniform(shader, name);
    glUniform1f(uni, val);
}

void shader::set_vec4(SHADER_UNIFORM, glm::vec4 val) {
    auto uni = shader::uniform(shader, name);
    glUniform4f(uni, val.x, val.y, val.z, val.w);
}

void shader::set_vec3(SHADER_UNIFORM, glm::vec3 val) {
    auto uni = shader::uniform(shader, name);
    glUniform3f(uni, val.x, val.y, val.z);
}

void shader::set_vec2(SHADER_UNIFORM, glm::vec2 val) {
    auto uni = shader::uniform(shader, name);
    glUniform2f(uni, val.x, val.y);
}

void shader::set_mat4(SHADER_UNIFORM, glm::mat4 matrix) {
    auto uni = shader::uniform(shader, name);
    glUniformMatrix4fv(uni, 1, GL_FALSE, &matrix[0][0]);
}
*/