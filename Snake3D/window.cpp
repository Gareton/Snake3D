#include "window.h"

Window::Window(sk_uint width, sk_uint height, const std::string& title)
	: _width(width), _height(height), _title(title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	_windowPtr = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

	if (_windowPtr == nullptr)
	{
		_errorMessage = "ERROR::GAME::INIT::GLFW_WINDOW_CREATION_FAILED";
		_isValid = false;
		return;
	}

	glfwMakeContextCurrent(_windowPtr);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		_errorMessage = "ERROR::GAME::INIT::GLAD_LOADER_FAILED";
		_isValid = false;
		return;
	}

	glfwSetInputMode(_windowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glViewport(0, 0, _width, _height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if(_wireframeMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Window::operator bool() const
{
	return _isValid;
}

sk_uint Window::getWidth() const
{
	return _width;
}

sk_uint Window::getHeight() const
{
	return _height;
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(_windowPtr);
}

bool Window::isPressed(sk_int key) const
{
	return glfwGetKey(_windowPtr, key) == GLFW_PRESS;
}

std::string Window::what() const
{
	return _errorMessage;
}

void Window::setWidth(sk_uint width)
{
	_width = width;
	glViewport(0, 0, _width, _height);
}

void Window::setHeight(sk_uint height)
{
	_height = height;
	glViewport(0, 0, _width, _height);
}

void Window::setCallbacks(WindowCallbacksInterface& callbacks)
{
	glfwSetWindowUserPointer(_windowPtr, (void*) &callbacks);

	auto resizeCallbackLambda = [](GLFWwindow* window, int width, int height)
	{
		static_cast<WindowCallbacksInterface *>(glfwGetWindowUserPointer(window))->resizeCallback(width, height);
	};

	auto mouseCallbackLambda = [](GLFWwindow* window, double xpos, double ypos)
	{
		static_cast<WindowCallbacksInterface *>(glfwGetWindowUserPointer(window))->mouseCallback(xpos, ypos);
	};

	auto scrollCallbackLambda = [](GLFWwindow* window, double xoffset, double yoffset)
	{
		static_cast<WindowCallbacksInterface *>(glfwGetWindowUserPointer(window))->scrollCallback(xoffset, yoffset);
	};

	auto mouseButtonLambda = [](GLFWwindow* window, int button, int action, int mods)
	{
		static_cast<WindowCallbacksInterface *>(glfwGetWindowUserPointer(window))->
												mouseButtonCallback(button, action, mods);
	};

	glfwSetFramebufferSizeCallback(_windowPtr, resizeCallbackLambda);
	glfwSetCursorPosCallback(_windowPtr, mouseCallbackLambda);
	glfwSetScrollCallback(_windowPtr, scrollCallbackLambda);
	glfwSetMouseButtonCallback(_windowPtr, mouseButtonLambda);
}

void Window::setCursorMode(sk_int mode)
{
	glfwSetInputMode(_windowPtr, GLFW_CURSOR, mode);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(_windowPtr);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::close()
{
	glfwSetWindowShouldClose(_windowPtr, true);
}