#include "../include/WindowManager.h"
#include "glfw3.h"
#include <cstdlib>
#include <iostream>
#include <cstring>

WindowManager::WindowManager(int& width, int& height, const std::string& title):mWidth(width),mHeight(height),mTitle(title){
	init(width,height,title);
}		

void WindowManager::init(int& width, int& height, const std::string& title){
	
	// GLFW initialization
	if(!glfwInit()){
		std::cerr<<"ERROR: GLFW could not initialize"<<std::endl;
		exit(EXIT_FAILURE);
	}

	// GLFW window hint
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// window creation
	mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), NULL, NULL);
	// window creation fail
	if(!mWindow){
		std::cerr<<"ERROR: GLFW window creation failed."<<std::endl;
		glfwTerminate();
	}

	// OpenGL context
	glfwMakeContextCurrent(mWindow);
	// For debugging
	glEnable(GL_DEBUG_OUTPUT);
	// vsync
	glfwSwapInterval(1);
}

GLFWwindow* WindowManager::getWindow(){return mWindow;}

void WindowManager::destroy(GLFWwindow* window){
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

int WindowManager::getWidth(){return mWidth;}
int WindowManager::getHeight(){return mHeight;}
const std::string WindowManager::getTitle(){return mTitle;}

