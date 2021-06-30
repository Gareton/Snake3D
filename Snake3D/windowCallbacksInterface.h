#ifndef WINDOW_CALLBACKS_INTERFACE
#define WINDOW_CALLBACKS_INTERFACE

class WindowCallbacksInterface
{
public:
	virtual ~WindowCallbacksInterface() {};
	virtual void resizeCallback(sk_uint width, sk_uint height) = 0;
	virtual void mouseCallback(sk_double xpos, sk_double ypos) = 0;
	virtual void scrollCallback(sk_double xoffset, sk_double yoffset) = 0;
};

#endif
