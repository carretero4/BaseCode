#include "game.h"
#include <stdlib.h> 

int main(int argc, char* args[])
{
	Game game;
	SDL_Event event;

	game.init("Entrega1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 500, false);

	while (game.isRunning())
	{
		while (SDL_PollEvent(&event)) {
			game.handleEvents(event);
		}
		game.update();
		game.render(255, 255, 255);
	}
	game.clean();
	return 0;
}