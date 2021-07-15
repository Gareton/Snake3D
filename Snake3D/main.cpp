#include <iostream>
#include <fstream>
#include "game.h"
#include "window.h"
#include "settings.h"
#include "snakeWorldController.h"
#include "snakeCameraController.h"

int main()
{
	try 
	{
		Window window(1000, 800, "Snake3D");
			

		if (!window)
			throw std::runtime_error(window.what());

		Game game(window);

		game.run();
	}

	catch (const std::exception& e)
	{
		std::ofstream log_output("log.txt");
		log_output << e.what() << std::endl;
		log_output.close();
		return -1;
	}
}