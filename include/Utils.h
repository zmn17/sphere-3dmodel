#ifndef UTIL_H
#define UTIL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Utils {
public:
  static void printShaderLog(GLuint shader);
  static void printProgramLog(int prog);
  static bool checkOpenGLError();
  static std::string readShaderSource(const std::string &filePath);

  static GLuint createShaderProgram(const std::string &vShaderFilePath,
                                    const std::string &fShaderFilePath);
  static GLuint createShaderProgram(const char *vp, const char *gp,
                                    const char *fp);
  static GLuint createShaderProgram(const char *vp, const char *tCS,
                                    const char *tES, const char *fp);
  static GLuint createShaderProgram(const char *vp, const char *tCS,
                                    const char *tES, const char *gp,
                                    const char *fp);
  // static GLuint loadTexture(const char *texImagePath);

  // GLuint createShaderProgram();
  // GLSL Functions for building MATRIX Transforms
  // builds and returns a translation matrix
  static glm::mat4 buildTranslate(float x, float y, float z);

  // builds and returns a matrix that performs a rotation around X axis
  static glm::mat4 buildRotateX(float rad);

  // builds and returns a matrix that performs a roration around Y axis
  static glm::mat4 buildRotateY(float rad);

  // builds and returns a matrix that performs a rotation around Z axis
  static glm::mat4 buildRotateZ(float rad);

  // builds and returns a scale matrix
  static glm::mat4 buildScale(float x, float y, float z);
};

#endif
