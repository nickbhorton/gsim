#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"

static unsigned int indexes[] = {
	0, 1, 2,
	1, 3, 2
};

static float basic_triangle_vertex_positions[] = {
    -1, -1,
	 1, -1,
	-1,  1,
	 1,  1
};

static float basic_triangle_vertex_colors[] = {
    1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 0.0, 0.0,
};

// VBOs
GLuint vertex_position_vbo {};
GLuint vertex_color_vbo {};

// VAOs
GLuint triangle_vao {};

// IBO
GLuint triangle_ibo {};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if( action == GLFW_PRESS){
		switch ( key ) {
			case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE); break;
			case GLFW_KEY_Q: glfwSetWindowShouldClose(window, GL_TRUE); break;
        }
	}
}
static void error_callback(int error, const char* description){
    std::cerr << "Error: " << description << "\n";
}

static void frame_buffer_size_callback(GLFWwindow* window, int width, int height){
    std::cout << "width: " << width << " height: " << height << "\n"; 
	glViewport(0,0,width,height);
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {

}

void init_gl_buffers(){

	// Generate VBO for vertex position data
	glGenBuffers(1, &vertex_position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_position_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(basic_triangle_vertex_positions), basic_triangle_vertex_positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Generate VBO for vertex color data
	glGenBuffers(1, &vertex_color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(basic_triangle_vertex_colors), basic_triangle_vertex_colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Generate IBO
	glGenBuffers(1, &triangle_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Generate VAO
	glGenVertexArrays(1, &triangle_vao);
	glBindVertexArray(triangle_vao);

	// Enable position attribute
	constexpr GLuint position_attrib = 0;
	constexpr GLuint vertex_position_dimension = 2;
	glEnableVertexAttribArray(position_attrib);
	// Bind position data VBO to VAO
	glBindBuffer(GL_ARRAY_BUFFER, vertex_position_vbo);
	glVertexAttribPointer(
		position_attrib, vertex_position_dimension, GL_FLOAT, GL_FALSE, sizeof(basic_triangle_vertex_positions[0]) * vertex_position_dimension, (GLvoid *) 0
	);

	// Enable color attribute
	constexpr GLuint color_attrib = 1;
	constexpr GLuint vertex_color_dimension = 3;
	glEnableVertexAttribArray(color_attrib);
	// Bind position data VBO to VAO
	glBindBuffer(GL_ARRAY_BUFFER, vertex_color_vbo);
	glVertexAttribPointer(
		color_attrib, vertex_color_dimension, GL_FLOAT, GL_FALSE, sizeof(basic_triangle_vertex_colors[0]) * vertex_color_dimension, (GLvoid *) 0
	);

	glBindVertexArray(0);
}

int main(int argc, char *argv[]){
    GLFWwindow* window;

	glfwSetErrorCallback(&error_callback);

    if(!glfwInit()){ 
		return EXIT_FAILURE; 
	}

    // Ask for OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the glfw window
	window = glfwCreateWindow(500, 500, "gsim", NULL, NULL);
	if(!window){ 
		glfwTerminate(); 
		return EXIT_FAILURE; 
	}

    // Callbacks
    glfwSetKeyCallback(window, &key_callback);
    glfwSetFramebufferSizeCallback(window, &frame_buffer_size_callback);

	glfwMakeContextCurrent(window); // Make the window current
    glfwSwapInterval(1); // Set the swap interval

    // make sure the openGL code can be found
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to gladLoadGLLoader" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

    // OpenGL initializations
	glEnable(GL_DEPTH_TEST);  // turn hidden surface removal on
	glEnable(GL_CULL_FACE); // Requires triangles to be defined ccw
	glClearColor(1.f,1.f,1.f,1.f);  // set the background

	// Shader initialization
	Shader default_shader {};
	default_shader.from_files("../res/basic.vert", "../res/basic.frag");
	default_shader.enable();

	init_gl_buffers();
	glBindVertexArray(triangle_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_ibo);

    while(!glfwWindowShouldClose(window)){
        // Clear the color and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glDrawElements(GL_TRIANGLES, sizeof(indexes), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
		glfwPollEvents();
    }

	glBindVertexArray(0);
	default_shader.disable();

    return EXIT_SUCCESS;
}