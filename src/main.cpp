#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if( action == GLFW_PRESS){
		switch ( key ) {
			case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE); break;
			case GLFW_KEY_Q: glfwSetWindowShouldClose(window, GL_TRUE); break;
        }
	}
}

int main(int argc, char *argv[]){
    GLFWwindow* window;
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

	glfwMakeContextCurrent(window); // Make the window current
    glfwSwapInterval(1); // Set the swap interval

    // make sure the openGL code can be found; folks using Windows need this
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to gladLoadGLLoader" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

    // OpenGL initializations
	glEnable(GL_DEPTH_TEST);  // turn hidden surface removal on
	glClearColor(1.f,1.f,1.f,1.f);  // set the background


    while(!glfwWindowShouldClose(window)){
        // Clear the color and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
		glfwPollEvents();
    }

    return EXIT_SUCCESS;
}