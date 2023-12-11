#ifndef GSIM_SHADER_HEADER_
#define GSIM_SHADER_HEADER_

#include "glad/glad.h"

class Shader {
    ~Shader();
    Shader()
        : program_id{0}
    {};


    // No copy or move assignment or constructor
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) noexcept = delete;
    Shader& operator=(const Shader& other) = delete;
    Shader& operator=(Shader&& other) noexcept = delete;

private:
    GLuint program_id;
	GLuint vertex_id;
	GLuint fragment_id;
};

#endif