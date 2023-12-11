#ifndef GSIM_SHADER_HEADER_
#define GSIM_SHADER_HEADER_

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "glad/glad.h"

class Shader {
public:
    Shader() : 
        program_id_{0},
        vertex_id_{0},
        fragment_id_{0}
    {};
    ~Shader(){
        glDeleteProgram(program_id_);
    };
    void enable();
    void disable();

    void from_files(std::string vertex_file_path, std::string fragment_file_path);
    GLuint uniform( const std::string name );

    // No copy or move assignment or constructor
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) noexcept = delete;
    Shader& operator=(const Shader& other) = delete;
    Shader& operator=(Shader&& other) noexcept = delete;

private:
    GLuint program_id_;
	GLuint vertex_id_;
	GLuint fragment_id_;

    std::unordered_map<std::string, GLuint> uniform_map;

    void init(std::string vertex_source, std::string fragment_source);
    int compile_source(const char* source, GLenum shader_type);
};

#endif