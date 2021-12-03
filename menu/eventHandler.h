#include <SDL2/SDL.h>
#include <vector>
#include "component.h"

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

using namespace std;
class EventHandler
{
	public:
		void handleEvent(SDL_Event event,State * state);
		void registerComponent(Component* c);
		static EventHandler * getInstance()
		{
			static int instanceCount = 0;
			if(instanceCount == 0 )
			{
				return new EventHandler();
				instanceCount ++;
			}
			else
				return NULL;
		}
	private:
		EventHandler(){}
		vector<Component*> components;	
};


void EventHandler::registerComponent(Component * c)
{
	this->components.push_back(c);
	cout << "Registered a component"<<endl;
}

void EventHandler::handleEvent(SDL_Event event,State * state)
{
	if(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			state->running = false;

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			for(int i =0; i < components.size(); i++)
			{
				if(components[i]->clicked(event.motion.x,event.motion.y))
				{
					cout << "Sending a click event"<<endl;
					components[i]->onclick();
				}
			}
		}
		if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_RETURN)
				state->current = (state->current >= 4)? 0:++state->current;
		}
	}
}

#endif
