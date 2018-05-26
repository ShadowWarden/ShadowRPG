/* main.cpp
 * Omkar H. Ramachandran
 * omkar.ramachandran@colorado.edu
 *
 * Test file for the engine code
 */

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "object.hpp"

GLFWwindow * window;

int main(){
	// Parameters	
	int height = 768;
	int width = 1024;
	float time_now = 0;
	float T = 5;

	// Initialize GLEW
	glewExperimental = true;
	
	if( !glfwInit() ){
		fprintf(stderr, "ERROR: Failed to initialize GLEW\n");
		return -1;
	}

	// Create the actual window!
	glfwWindowHint(GLFW_SAMPLES, 4);	// 4x Anti-aliasing
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);	// Want OpenGL 3.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


	// This line makes sure that we don't get the old-style OpenGL
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create it's OpenGL context
	window = glfwCreateWindow(width, height, "05_textures", NULL, NULL);

	if(window == NULL){
		fprintf(stderr, "Failed to open GLFW window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	// Initialize GLEW
	if(glewInit() != GLEW_OK){
		fprintf(stderr, "ERROR: Failed to initialize GLEW\n");
		glfwTerminate();
		return -1;
	}	

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Create Projection Matrix
	glm::mat4 Projection = glm::perspective(
			glm::radians(45.0f), 			// Field of View
			(float) width/(float) height, 	// Aspect Ratio
			0.1f,							// Near clipping plane of camera Frustum
			100.0f							// Far clipping plane
			);


	// Camera Matrix
	glm::mat4 View = glm::lookAt(
			glm::vec3(8,4,6),		// Camera Position in world frame
			glm::vec3(0,4,0),		// Look at (0,0,0)
			glm::vec3(0,1,0)		// 'Up' direction in Camera coordinates
			);
	
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	fprintf(stdout, "DEBUG:Initialized VertexArray\n");

	Object obj("pillar.obj", "pillar.bmp", "vertex.vs", "frag.fs");

	bool close = false;
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj.Animate();	
		obj.render(Projection,View);
		
		glfwSwapBuffers(window);
		glfwPollEvents();

		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			close = true;

	}while( !close && (glfwWindowShouldClose(window) == 0));


	glfwTerminate();
	return 0;
}
