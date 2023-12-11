#include "Shader.h"

void Shader::enable() {
    if(program_id_ != 0){
        glUseProgram(program_id_);
    }
    else {
        std::cerr << "Error: shader was not initialized when enable() was called.\n";
        exit(EXIT_FAILURE);
    }
}

void Shader::disable() {
    glUseProgram(0);
}

void Shader::from_files(std::string vertex_file_path, std::string fragment_file_path)
{
    std::string vertex_source;
	std::ifstream vertex_stream(vertex_file_path, std::ios::in | std::ios::binary);
	if(vertex_stream){ 
        vertex_source = std::string(std::istreambuf_iterator<char>(vertex_stream), std::istreambuf_iterator<char>()); 
    }
	else{ 
        std::cerr << "Failed to load \"" << vertex_file_path << "\" shader program.\n";
        exit(EXIT_FAILURE);
    }


    std::string fragment_source;
	std::ifstream fragment_stream(fragment_file_path, std::ios::in | std::ios::binary);
	if(fragment_stream){ 
        fragment_source = std::string(std::istreambuf_iterator<char>(fragment_stream), std::istreambuf_iterator<char>()); 
    }
	else{ 
        std::cerr << "Failed to load \"" << fragment_file_path << "\" shader program.\n";
        exit(EXIT_FAILURE);
    }

	init(vertex_source, fragment_source);
}

GLuint Shader::uniform(const std::string name)
{
    // Create GLuint map from string if it doesn't already exist
    if(uniform_map.count(name) == 0){ 
		uniform_map[name] = glGetUniformLocation(program_id_, name.c_str());
		if(uniform_map[name] < 0){ 
            std::cout << "getting uniform location returned a negative number\n";
            exit(EXIT_FAILURE); 
        }
	}
	return uniform_map[name];
}

void Shader::init(std::string vertex_source, std::string fragment_source)
{
    program_id_ = glCreateProgram();
    if (program_id_ == 0){
        std::cerr << "Failed to create GL program id.\n";
        exit(EXIT_FAILURE);
    }

    vertex_id_ = compile_source(vertex_source.c_str(), GL_VERTEX_SHADER);
	fragment_id_ = compile_source(fragment_source.c_str(), GL_FRAGMENT_SHADER);

    // Attach and link the program
	glAttachShader(program_id_, vertex_id_);
	glAttachShader(program_id_, fragment_id_);
	glLinkProgram(program_id_);

	// Once the shader program has the shaders attached and linked, the shaders are no longer required.
	// If the linking failed, then we're going to abort anyway so we still detach the shaders.
	glDetachShader(program_id_, vertex_id_);
	glDetachShader(program_id_, fragment_id_);

	GLint program_link_status = GL_FALSE;
	glGetProgramiv(program_id_, GL_LINK_STATUS, &program_link_status);
	if(program_link_status != GL_TRUE) { 
        GLint program_log_length = 0;
	    glGetProgramiv(program_log_length, GL_INFO_LOG_LENGTH, &program_log_length);
        std::cerr << "link status int: " << program_link_status << "\n";
        std::cerr << "log info length: " << program_log_length << "\n";
        std::cerr << "Failed to link shader program.\n";
        exit(EXIT_FAILURE);
    }

	glUseProgram(0);
}

GLint Shader::compile_source(const char* source, GLenum shader_type) {
    GLint shader_id = glCreateShader(shader_type);
    if (shader_id == 0){
        std::cerr << "Failed to create GL shader id of type number " << shader_type << ".\n";
        exit(EXIT_FAILURE);
    }

    glShaderSource(shader_id, 1, &source, NULL);
	glCompileShader(shader_id);

    // Handling failure
    GLint shader_status = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &shader_status);
	if(shader_status != GL_TRUE){ 
        std::cerr << "Failed to compile shader of type number " << shader_type << ".\n";
        exit(EXIT_FAILURE);
    }
    // TODO: better failure suggestions
    return shader_id;
}