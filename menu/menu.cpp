#include <SDL2/SDL.h>
#include "scene.h"
#include "button.h"
#include "eventHandler.h"

#ifndef MENU_H
#define MENU_H

#include <iostream>
using namespace std;


class Menu: public Scene
{
	string name;
	bool active;
	SDL_Color bg;
	public:

	Menu(){}
	Menu(string name,EventHandler * handler);
	void setBgColor(Uint8 r,Uint8 g,Uint8 b)
	{
		this->bg = {r,g,b};
	}
	static void playCallback();
	static void optionCallback();
	void draw();
	Button *play,*option;
};

void Menu::playCallback()
{
	cout << "Received click event"<<endl;
}

Menu::Menu(string name,EventHandler * handler)
{
	this->name = name;
	this->bg = {0xf3,0xe0,0xaa};	
	this->play = new Button("my btn",100,100,playCallback);
	this->play->rect.w = 100;
	this->play->rect.h = 30;
	handler->registerComponent((Component *)this->play);
}

void Menu::draw()
{
	SDL_SetRenderDrawColor(this->sRenderer,bg.r,bg.g,bg.b,0xff);
	SDL_RenderClear(this->sRenderer);
	SDL_SetRenderDrawColor(this->sRenderer,0x32,0x43,0x54,0xff);
	SDL_RenderFillRect(this->sRenderer,&this->play->rect);
	SDL_RenderPresent(this->sRenderer);
}


#endif // MENU_H
