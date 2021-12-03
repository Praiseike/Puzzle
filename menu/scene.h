
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;
#ifndef SCENE_H
#define SCENE_H

class Scene
{
	public:
	Scene(){}
	void replace(SDL_Window *window);
	virtual void draw();
	
	protected:
	SDL_Renderer * sRenderer;
};


void Scene::replace(SDL_Window * window)
{
	SDL_DestroyRenderer(SDL_GetRenderer(window));
	this->sRenderer = SDL_CreateRenderer(window,-1,0);
	if(!this->sRenderer)
		cout << "Unable to create scene renderer: "<<SDL_GetError()<<endl;

}
void Scene::draw()
{
	SDL_RenderClear(this->sRenderer);
	SDL_RenderPresent(this->sRenderer);
}
#endif
