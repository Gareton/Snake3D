#ifndef MENU_CALLBACKS_INTERFACE_H
#define MENU_CALLBACKS_INTERFACE_H

enum GAME_STATUS;
enum SNAKE_CONTROLLER_TYPE;

class MenuCallbacksInterface
{
public:
	virtual void switchSnakeController(SNAKE_CONTROLLER_TYPE controllerType) = 0;
	virtual void switchGameStatus(GAME_STATUS gameStatus) = 0;

	virtual ~MenuCallbacksInterface() {}
};

#endif
