#include "shader.h"
#include <utils/logger.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void shader::compile(GLuint shader, const char *data) {
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

Shader shader::load(const char *vertex, const char *fragment) {
    auto vid = glCreateShader(GL_VERTEX_SHADER);
    auto fid = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vcode;
    std::string fcode;

    std::ifstream vstream(vertex, std::ios::in);
    std::ifstream fstream(fragment, std::ios::in);

    if (!vstream.is_open()) {
        logger::logf("vertex shader path not found.\n");
    }

    if (!fstream.is_open()) {
        logger::logf("fragment shader path not found.\n");
    }

    std::stringstream ss;

    ss << vstream.rdbuf();
    vcode = ss.str();
    vstream.close();

    ss.str("");

    ss << fstream.rdbuf();
    fcode = ss.str();
    fstream.close();

    logger::logf("Loading vertex shader... -- (\"%s\")\n", vertex);
    compile(vid, vcode.c_str());

    logger::logf("Loading fragment shader... -- (\"%s\")\n", fragment);
    compile(fid, fcode.c_str());

    auto pid = glCreateProgram();

    glAttachShader(pid, vid);
    glAttachShader(pid, fid);
    glLinkProgram(pid);

    glDetachShader(pid, vid);
    glDetachShader(pid, fid);

    glDeleteShader(vid);
    glDeleteShader(fid);
    logger::logf("Compiled both shaders! -- ('%s', '%s')\n", vertex, fragment);
    return pid;
}

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
