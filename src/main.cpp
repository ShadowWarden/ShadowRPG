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
#include "controls.hpp"

GLFWwindow * window;

int main(){
	// Parameters	
	int height = 768;
	int width = 1024;

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
			45.0f,
			4.0f/3.0f,
			0.1f,
			100.0f);

	// Camera Matrix
	glm::mat4 View = glm::lookAt(
			glm::vec3(8,6,6),
			glm::vec3(0,4,0),
			glm::vec3(0,1,0)
			);
	
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	fprintf(stdout, "DEBUG:Initialized VertexArray\n");

	Object obj1("pillar.obj", "pillar.bmp", "pillar_normals.bmp", "vertex.vs", "frag.fs",2,0);
	Object obj2("pillar.obj", "pillar.bmp", "pillar_normals.bmp", "vertex.vs", "frag.fs",-2,0);

	fprintf(stdout,"DEBUG: Initialized fonts\n");

	bool close = false;
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	char fps[256];
	sprintf(fps,"0 FPS");

	float R = 8;
	float theta = 3.1415/2;
	float phi = 3.1415;
	float speed = 3.1415/2.5;

	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f),3.1415f/2.0f,glm::vec3(1,0,0));

	do{
		double currentTime = glfwGetTime();
		nbFrames ++;
		if(currentTime - lastTime >= 5.0){
			fprintf(stdout, "DEBUG: %s\n", fps);
			sprintf(fps,"%d FPS",nbFrames/5);
			nbFrames = 0;
			lastTime += 5.0;
			phi = 0;
		}

		//computeMatricesFromInputs();
		//Projection = getProjectionMatrix();
		//View = getViewMatrix();

		phi = speed*(currentTime-lastTime);

		glm::vec4 pos = glm::vec4(R*glm::sin(theta)*glm::cos(phi),
				R*glm::sin(theta)*glm::sin(phi),
				R*glm::cos(theta),0);


		glm::vec4 lightPos4x4 = rotate*pos;

		glm::vec3 lightPos = glm::vec3(lightPos4x4);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		obj1.Animate();	
		obj2.Animate();

		obj1.render(Projection,View,lightPos);
		obj2.render(Projection,View,lightPos);
			
		glfwSwapBuffers(window);
		glfwPollEvents();

		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			close = true;

	}while( !close && (glfwWindowShouldClose(window) == 0));


	glfwTerminate();
	return 0;
}
