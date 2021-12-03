#include <SDL2/SDL.h>
#include <iostream>
#include "base.h"
#include "menu.cpp"
#include "menu.h"
#include "eventHandler.h"


#define Error(msg) cout <<msg<<": "<< SDL_GetError() <<endl;
using namespace std;

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;
SDL_Event event;
EventHandler * eventHandler;
Menu m;

State state;


int main()
{
	if(SDL_Init(SDL_INIT_VIDEO != 0))
	{
		Error("Failed to init SDL");
	}
	window = SDL_CreateWindow("My Menu",0,0,400,400,SDL_WINDOW_SHOWN);
	if(!window)
	{
		Error("Failed to Create Window"); 
		return -1;
	}

	renderer = SDL_CreateRenderer(window,-1,0);
	if(!renderer)
	{
		Error("Failed to create renderer");
		return -1;
	}

	SDL_SetRenderDrawColor(renderer,0xd3,0xd3,0xd3,0xa);
	eventHandler = EventHandler::getInstance();
	state.running = true;
	m = Menu("fjk",eventHandler);
	m.replace(window);
	while(state.running)
	{
		m.draw();
		eventHandler->handleEvent(event,&state);
	}

	delete eventHandler;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
