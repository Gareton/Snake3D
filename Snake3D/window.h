#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window 
{
public:
	Window(size_t windowWidth = 800,
		   size_t windowHeight = 600,
		   const std::string& windowTitle = "Snake3D");

	Window(const Window& o) = delete;
	Window& operator=(const Window& o) = delete;

	operator bool();
	std::string what();
	GLFWwindow* getWindowPtr();
	size_t getWindowWidth();
	size_t getWindowHeight();
	void setWindowWidth(size_t width);
	void setWindowHeight(size_t height);
private:
	GLFWwindow* _window;
	bool _isValid;
	std::string _errorMessage;
	size_t _windowWidth;
	size_t _windowHeight;
	const std::string _windowTitle;
	const bool _wireframeMode = false;
};

#endif
