// TODO:
// 1. initialize GLFW - done
// 2. set GLFW window hints - done
// 3. create and manage the window - done
// 4. setup opengl context - done
// 5. handle window cleanup and destruction - done
//
// the class should store:
// a. a pointer to the GLFWwindow b. some config - widht,height,title - done
// 
// public interface - 
//	a. define clear public method for:
//		- initializing the window - done
//		- getting the GLFWwindow* for use in render loop - done
//		- polling events, swapping buffers
//		- terminating and cleanup
//
//	life cylce management -
//		- constructor for setup (or a separate init method)
//		- desctructor for cleanup (glfwDestroyWindow)
//
//	Encapsulation - 
//		- keep all glfw-specific login internal to the classs to avoid leaking implementation
//
//	Usage - 
//		- create an instance of the window class
//		- use its public methods to interact with window
//
#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H

#include <GLFW/glfw3.h>
#include <string>
class WindowManager {
public:
	WindowManager(int width, int height, const std::string& title);
	WindowManager(WindowManager &&) = default;
	WindowManager(const WindowManager &) = default;
	WindowManager &operator=(WindowManager &&) = default;
	WindowManager &operator=(const WindowManager &) = default;
	~WindowManager();

	void init(int width, int height, const std::string& title);
	void destroy(GLFWwindow* window);
	GLFWwindow* getWindow();
	int getWidth();
	int getHeight();
	const std::string getTitle();
private:
	GLFWwindow* mWindow;
	int mHeight;
	int mWidth;
	std::string mTitle;
};

#endif // !WINDOW_MGR_H
