#include <GL/glew.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../external/include/Utils.h"
#include "../external/include/WindowManager.h"
#include "../include/Sphere.h"

// Vertex Array objects
#define numVAOs 1
// Vertex Buffer objects
#define numVBOs 3

// camera position
float cameraX, cameraY, cameraZ;

// Rendering program
GLuint renderinProgram;
GLuint worldTexture;

// Buffer/array holds id of vertex and buffer objects
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// matrices location in shaders
GLuint projLoc, mvLoc;

// windows resoultion
int width, height;
float aspect;

// matrices
glm::mat4 pMat, vMat, mMat, mvMat;

// sphere init
Sphere sphere(48);

// sphere vertices setup
void setupVertices(void){
	std::vector<int> ind = sphere.getIndices();
	std::vector<glm::vec3> vert = sphere.getVertices();
	std::vector<glm::vec2> text = sphere.getTexCoords();
	std::vector<glm::vec3> norm = sphere.getNormals();

	std::vector<float> pvalues; // vertex positions
	std::vector<float> tvalues; // texture coordinates
	std::vector<float> nvalues; // normal vectors
	
	int numIndices = sphere.getNumIndices();
	for(int i = 0; i < numIndices; i++){
		pvalues.push_back((vert[ind[i]]).x);
		pvalues.push_back((vert[ind[i]]).y);
		pvalues.push_back((vert[ind[i]]).z);

		tvalues.push_back((text[ind[i]]).s);
		tvalues.push_back((text[ind[i]]).t);

		nvalues.push_back(norm[ind[i]].x);
		nvalues.push_back(norm[ind[i]].y);
		nvalues.push_back(norm[ind[i]].z);
	}
	// generate a vertex array
	glGenVertexArrays(numVAOs, vao);
	// activate the first vertex array 
	glBindVertexArray(vao[0]);
	
	// generate a vertex buffer object
	glGenBuffers(numVBOs, vbo);

	// put the vertices into buffer #0
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size()*4, &pvalues[0], GL_STATIC_DRAW);

	// put the texture coordinates into buffer #1
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tvalues.size()*4, &tvalues[0], GL_STATIC_DRAW);

	// put the normals into buffer #2
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nvalues.size()*4, &nvalues[0], GL_STATIC_DRAW);

}

void init(GLFWwindow* window){
	// create shader program
	renderinProgram = Utils::createShaderProgram("/home/zee/dev/sphere/shaders/vshader.glsl", "/home/zee/dev/sphere/shaders/fshader.glsl");

	if(Utils::checkOpenGLError()){
		std::cerr<<"ERORR: shader program creation failed."<<std::endl;
	}

	glfwGetFramebufferSize(window, &width, &height);
	aspect = static_cast<float>(width) / static_cast<float>(height);

	// projection matrix
	pMat = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

	// camera position init
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = 4.0f;

	// texture loading
	std::cout<<"Loading texture ... "<<std::endl;
	worldTexture = Utils::LoadTexture("/home/zee/dev/sphere/textures/world.jpg");
	if(worldTexture == 0){
		std::cerr<<"Could not open the texture file.\n";
		exit(EXIT_FAILURE);
	}
	std::cout<<"[init] Texture loaded OK\n";
	
	// setup vertices for model
	setupVertices();
	std::cout<<"[init] setupVertices() complete."<<std::endl;

}
void display(GLFWwindow* window, double currTime){
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// use renderinProgram
	glUseProgram(renderinProgram);

	// get position of project matrix and model-view in shaders - using uniform variable
	projLoc = glGetUniformLocation(renderinProgram, "proj_matrix");
	mvLoc = glGetUniformLocation(renderinProgram, "mv_matrix");
	
	// create a view matrix - TRANSLATION
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

	// create a model matrix - ROTATION
	float angle = glm::radians(45.0f);
	mMat = glm::rotate(glm::mat4(1.0f), (float)currTime, glm::vec3(1.0f, 0.0f, 0.0f));
	
	// create Model-View matrix - 
	mvMat = vMat * mMat;

	// passing pointer from projection matrix to matrix in shaders
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	// same with model-view matrix
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));

	// make the first vertex array active
	glBindVertexArray(vao[0]);

	// make first vertex buffer active
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, worldTexture);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glDrawArrays(GL_TRIANGLES, 0, sphere.getNumIndices());
}

int main(void){
	// Window creation
	WindowManager* windowmgr = new WindowManager(1080, 720, "Sphere");
	GLFWwindow* win = windowmgr->getWindow();

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

