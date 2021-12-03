#ifndef CUSTOM_BTN_H
#define CUSTUM_BTN_H
#include <SDL2/SDL.h>
#include "component.h"

class Button : public Component
{

	public:
		Button(string text,int x,int y ,void (*func)());
		Button(string text,SDL_Rect rect,void (*func)());
		Button(string text,SDL_Rect rect);
		void onclick()
		{
			this->callback();
		}

	private:
		void (*callback)() = NULL;
		string text;
		int id;
		// attributes for the future 
		bool disabled;
		bool active;

};


Button::Button(string text,int x,int y,void (*func)())
{
	this->text = text;
	this->rect.x = x;
	this->rect.y = y;
	this->callback = func;
}

Button::Button(string text,SDL_Rect rect,void (*func)())
{
	this->text = text;
	this->rect = rect;
	this->callback = func;
}



#endif
