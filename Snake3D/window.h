#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "skTypes.h"
#include <functional>
#include "windowCallbacksInterface.h"

class Window
{
public:
	Window(sk_uint width, sk_uint height, const std::string& title);
	Window(const Window& o) = delete;
	Window& operator=(const Window& o) = delete;

	operator bool() const;
	sk_uint getWidth() const;
	sk_uint getHeight() const;
	bool shouldClose() const;
	bool isPressed(sk_int key) const;

	void setWidth(sk_uint width);
	void setHeight(sk_uint height);
	void setCallbacks(WindowCallbacksInterface& callbacks);
	void setCursorMode(sk_int mode);

	void swapBuffers();
	void pollEvents();
	void close();
private:
	GLFWwindow* _windowPtr;
	bool _isValid = true;
	std::string _errorMessage;
	sk_uint _width;
	sk_uint _height;
	const std::string _title;
	const bool _wireframeMode = false;
};

#endif
