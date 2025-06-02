
<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/7/74/OpenGL_Logo.svg" alt="OpenGL Logo" width="200"/>
</p>

<h1 align="center">🌐 Textured Sphere Renderer</h1>

<p align="center">
  A simple OpenGL application to render a 3D textured sphere using GLFW, GLEW, GLM, and custom shaders.
</p>

---

## 🚀 Features

- ✅ Real-time rendering of a 3D sphere
- 🌍 Texture mapping using a world map
- 🌀 Dynamic rotation based on system time
- 🔧 Modular structure with utilities and window management
- 🎯 Uses modern OpenGL (Shader-based pipeline)

---

## 📸 Preview

*(Add a GIF or image of the rendered sphere here)*  
> _Example:_  
> ![sphere-preview](./preview.gif)

---

## 🧱 Built With

- [OpenGL](https://www.opengl.org/)
- [GLFW](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)
- [GLM](https://github.com/g-truc/glm)
- Custom `Sphere`, `Utils`, and `WindowManager` classes

---

## 📁 Project Structure

```
/sphere
├── include/
│   └── Sphere.h
├── external/include/
│   ├── Utils.h
│   └── WindowManager.h
├── shaders/
│   ├── vshader.glsl
│   └── fshader.glsl
├── textures/
│   └── world.jpg
├── main.cpp
└── ...
```

---

## 🧠 How It Works

### 🔹 Vertex Data Setup

Sphere geometry (vertices, normals, texture coordinates) is generated using the `Sphere` class and loaded into GPU buffers (VAOs & VBOs).

### 🔹 Shader Program

Vertex and fragment shaders transform the model, apply lighting, and map a texture (e.g., world map) to the surface.

### 🔹 Matrix Transformations

- **Model Matrix**: Applies a rotation  
- **View Matrix**: Positions the virtual camera  
- **Projection Matrix**: Perspective transformation

---

## 🛠️ Getting Started

### 🔧 Prerequisites

Make sure the following libraries are installed:

```bash
sudo pacman -S glew glfw glm
```

### 🧪 Build and Run

```bash
g++ main.cpp -o sphere -lGL -lGLEW -lglfw
./sphere
```

> ℹ️ Update the include paths and texture/shader locations if your directory structure differs.

---

## 🧾 Shader Example

**Vertex Shader (`vshader.glsl`)**:
```glsl
#version 460

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;

out vec2 tc;
uniform mat4 proj_matrix;
uniform mat4 mv_matrix;

void main(void){
	gl_Position = proj_matrix * mv_matrix * vec4(pos, 1.0);
	tc = texCoord;
}
```

**Fragment Shader (`fshader.glsl`)**:
```glsl
#version 460

in vec2 tc;
out vec4 color;

layout(binding=0) uniform sampler2D samp;

void main(void){
	color = texture(samp, tc);
}

```

---

## 📚 Credits

- Texture: [NASA Earth texture](https://visibleearth.nasa.gov/)

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

---

## 💬 Contact

Feel free to reach out or contribute!

> GitHub: [@zmn17](https://github.com/zmn17)  
> Email: *zmnahm17@gmail.com*
