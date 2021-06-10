#include "window.h"

Window::Window(sk_uint windowWidth,
			   sk_uint windowHeight,
			   const std::string& windowTitle)
	: _windowWidth(windowWidth), _windowHeight(windowHeight), _windowTitle(windowTitle), _isValid(true)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);

	if (_window == nullptr)
	{
		_errorMessage = "ERROR::GAME::INIT::GLFW_WINDOW_CREATION_FAILED";
		return;
	}

	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		_errorMessage = "ERROR::GAME::INIT::GLAD_LOADER_FAILED";
		return;
	}

	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glViewport(0, 0, windowWidth, windowHeight);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if(_wireframeMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Window::operator bool()
{
	return _isValid;
}


std::string Window::what()
{
	return _errorMessage;
}

GLFWwindow* Window::getWindowPtr()
{
	return _window;
}

sk_uint Window::getWindowWidth()
{
	return _windowWidth;
}

sk_uint Window::getWindowHeight()
{
	return _windowHeight;
}

void Window::setWindowWidth(sk_uint width)
{
	_windowWidth = width;
}

void Window::setWindowHeight(sk_uint height)
{
	_windowHeight = height;
}
