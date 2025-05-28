#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/WindowManager.h"
#include "../include/Sphere.h"

void init(GLFWwindow* window){}
void display(GLFWwindow* window, double currTime){}

int main(void){
	// Window creation
	WindowManager* windowmgr;
	GLFWwindow* win = windowmgr->getWindow();
	windowmgr->init(1080, 720, "Sphere");

	// window initialization for rendering
	init(win);

	// rendering loop
	while(!glfwWindowShouldClose(win)){
		display(win, glfwGetTime());
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// Window destruction
	windowmgr->destroy(win);

	// window deletion
	delete windowmgr;

	return 0;
}

