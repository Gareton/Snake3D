#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "skTypes.h"

class Window 
{
public:
	Window(sk_uint windowWidth = 800,
		   sk_uint windowHeight = 600,
		   const std::string& windowTitle = "Snake3D");

	Window(const Window& o) = delete;
	Window& operator=(const Window& o) = delete;

	operator bool();
	std::string what();
	GLFWwindow* getWindowPtr();
	sk_uint getWindowWidth();
	sk_uint getWindowHeight();
	void setWindowWidth(sk_uint width);
	void setWindowHeight(sk_uint height);
private:
	GLFWwindow* _window;
	bool _isValid;
	std::string _errorMessage;
	sk_uint _windowWidth;
	sk_uint _windowHeight;
	const std::string _windowTitle;
	const bool _wireframeMode = false;
};

#endif
