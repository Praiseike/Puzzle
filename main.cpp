#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "puzzle.cpp"

#define WIDTH 340
#define HEIGHT 600

using namespace std;

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;
SDL_Event event;

bool running = false;

Puzzle * puzzle;

void render()
{

	SDL_RenderClear(renderer);
	puzzle->draw(renderer);;
	SDL_SetRenderDrawColor(renderer,0xf3,0xf3,0xf3,0xff);
	SDL_RenderPresent(renderer);
}

void handleEvents()
{
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			running = false;
		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			for(int id = 0; id < 9; id ++ )
			{
				if(puzzle->tiles[id]->check_bounds(event.motion.x,event.motion.y))
				{
					puzzle->handleclick(id);
				}
			}		
		}
	}
}

int main(int argc,char ** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		cout << "Initialized SDL library"<<endl;
		IMG_Init(IMG_INIT_JPG);
		window = SDL_CreateWindow("puzzle 1.0",0,0,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
		if(window)
		{
			renderer = SDL_CreateRenderer(window,-1,0);
			if(!renderer)
				cerr << "Unable to create renderer"<<endl;
		}else{
			cerr << "Unable to create window"<<endl;
			return -1;
		}
	}else{
		cerr << "Unable to init SDL "<<endl;
		return -1;
	}
	SDL_SetRenderDrawColor(renderer,65,54,43,1);
	running = true;


	const char * filename = "image.jpg";
	if (argc > 1)
		filename = argv[1];

	puzzle = new Puzzle();
	puzzle->loadImage(renderer,filename);	
	

	while(running)
	{
		render();
		handleEvents();
	}
	delete puzzle;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}

