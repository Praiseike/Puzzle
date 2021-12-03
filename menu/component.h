#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
	protected:
	public:
		Component(){}
		SDL_Rect rect;
		bool clicked(int x,int y);
		virtual void onclick(){cout << "Stuff happend"<<endl;}

};
		
bool Component::clicked(int x,int y)
{
	if (this->rect.x <= x && this->rect.x+this->rect.w >= x)
		if(this->rect.y <= y && this->rect.y+this->rect.h >= y)
			return true;
	return false;
}


#endif
