#include "../include/Utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/resource.h>

void Utils::printShaderLog(GLuint shader) {
  int len = 0;
  int chWittn = 0;
  char *log;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
  if (len > 0) {
    log = (char *)malloc(len);
    glGetShaderInfoLog(shader, len, &chWittn, log);
    std::cout << "Shader Info Log: " << log << std::endl;
    free(log);
  }
}

void Utils::printProgramLog(int prog) {
  int len = 0;
  int chWittn = 0;
  char *log;

  glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
  if (len > 0) {
    log = (char *)malloc(len);
    glGetProgramInfoLog(prog, len, &chWittn, log);
    std::cout << "Program Info Log: " << log << std::endl;
    free(log);
  }
}

bool Utils::checkOpenGLError() {
  bool foundError = false;
  int glError = glGetError();
  while (glError != GL_NO_ERROR) {
    std::cout << "glError: " << glError << std::endl;
    foundError = true;
    glError = glGetError();
  }
  return foundError;
}

std::string Utils::readShaderSource(const std::string &filePath) {
  // open the file in read mode
  std::ifstream fileStream(filePath, std::ios::in);
  if (!fileStream.is_open()) {
    std::cerr << "Error: Could not open shader file: " << filePath << std::endl;
    return "";
  }
  // create a strin stream buffer
  std::stringstream buffer;
  // redirects/output the contens of filestream buffer into buffer
  buffer << fileStream.rdbuf();

  fileStream.close();
  // return the contents of the buffer
  return buffer.str();
}
/*
@brief creates, compiles, and links shaders into a shader program.
*/
GLuint Utils::createShaderProgram(const std::string &vShaderFilePath,
                                  const std::string &fShaderFilePath) {
  GLint vertCompiled;
  GLint fragCompiled;
  GLint linked;

  // read the shader code from file
  std::string verShaderSrc = readShaderSource(vShaderFilePath);
  std::string fragShaderSrc = readShaderSource(fShaderFilePath);

  // check if the shaders empty
  if (verShaderSrc.empty() || fragShaderSrc.empty()) {
    std::cerr << "ERROR: Shader source is empty!" << std::endl;
    return 0;
  }

  // convert it to c-style string
  const char *vertShaderCode = verShaderSrc.c_str();
  const char *fragShaderCode = fragShaderSrc.c_str();

  // create vertex and fragment shader objects
  GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

  // loads the source code into vertex objects
  glShaderSource(vShader, 1, &vertShaderCode, NULL);

  // Check the vertex shader
  std::cout << "Compiling vertex shader: " << vShaderFilePath << std::endl;
  // compile the shader objects
  glCompileShader(vShader);
  checkOpenGLError();
  glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
  if (vertCompiled != 1) {
    std::cerr << "Vertex compilation failed." << std::endl;
  }
  printShaderLog(vShader);

  // load the source code into fragment shader objects
  glShaderSource(fShader, 1, &fragShaderCode, NULL);

  // Check the fragment shader
  std::cout << "Compiling fragment shader: " << fShaderFilePath << std::endl;
  glCompileShader(fShader);
  checkOpenGLError();
  glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
  if (fragCompiled != 1) {
    std::cerr << "Fragment compilation failed" << std::endl;
  }
  printShaderLog(fShader);

  GLuint vfProgram = glCreateProgram();
  glAttachShader(vfProgram, vShader);
  glAttachShader(vfProgram, fShader);

  glLinkProgram(vfProgram);
  checkOpenGLError();
  glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
  if (linked != 1) {
    std::cerr << "Program linking failed." << std::endl;
    printProgramLog(vfProgram);
  }

  glDeleteShader(vShader);
  glDeleteShader(fShader);

  return vfProgram;
}

// GLuint Utils::loadTexture(const char *texImagePath) {
//   GLuint textureID;
//   textureID = SOIL_load_OGL_texture(texImagePath, SOIL_LOAD_AUTO,
//                                     SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
//   if (textureID == 0) {
//     std::cout << "ERROR: could not find the texture file" << texImagePath
//               << std::endl;
//   }
//   glBindTexture(GL_TEXTURE_2D, textureID);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//                   GL_LINEAR_MIPMAP_LINEAR);
//   glGenerateMipmap(GL_TEXTURE_2D);
//
//   // anisotropic filtering
//   if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
//     GLfloat anisoSetting = 0.0f;
//     glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
//   }
//
//   return textureID;
// }

// builds and returns a translation matrix
glm::mat4 Utils::buildTranslate(float x, float y, float z) {
  glm::mat4 trans = glm::mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
                              1.0, 0.0, x, y, z, 1.0);
  return trans;
}

// builds and returns a matrix that performs a rotation around X axis
glm::mat4 Utils::buildRotateX(float rad) {
  glm::mat4 xrot = glm::mat4(1.0, 0.0, 0.0, 0.0, 0.0, cos(rad), -sin(rad), 0.0,
                             0.0, sin(rad), cos(rad), 0.0, 0.0, 0.0, 0.0, 1.0);
  return xrot;
}

// builds and returns a matrix that performs a roration around Y axis
glm::mat4 Utils::buildRotateY(float rad) {
  glm::mat4 yrot = glm::mat4(cos(rad), 0.0, sin(rad), 0.0, 0.0, 1.0, 0.0, 0.0,
                             -sin(rad), 0.0, cos(rad), 0.0, 0.0, 0.0, 0.0, 1.0);
  return yrot;
}

// builds and returns a matrix that performs a rotation around Z axis
glm::mat4 Utils::buildRotateZ(float rad) {
  glm::mat4 zrot = glm::mat4(cos(rad), -sin(rad), 0.0, 0.0, sin(rad), cos(rad),
                             0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  return zrot;
}

// builds and returns a scale matrix
glm::mat4 Utils::buildScale(float x, float y, float z) {
  glm::mat4 scale = glm::mat4(x, 0.0, 0.0, 0.0, 0.0, y, 0.0, 0.0, 0.0, 0.0, z,
                              0.0, 0.0, 0.0, 0.0, 1.0);
  return scale;
}
