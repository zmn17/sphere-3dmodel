#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>

class Sphere {
public:
	Sphere();
	Sphere(int prec);
	int getNumVertices();
	int getNumIndices();
	std::vector<int>getIndices();
	std::vector<glm::vec3>getVertices();
	std::vector<glm::vec2>getTexCoords();
	std::vector<glm::vec3>getNormals();

private:
	int numVertices;
	int numIndices;
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	void init(int);
	float toRadians(float degrees);
	
};
#endif // !SPHERE_H
