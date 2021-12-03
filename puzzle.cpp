#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <time.h>
#include <iostream>
#include <vector>

#ifndef PUZZLE_H
#define PUZZLE_H
#endif // PUZZLE_H

using namespace std;

class Tile{
	public:
		SDL_Rect src,rect;
		SDL_Color color;
		bool empty = false;
		Uint8 id;
		Tile(Uint8 id,unsigned int x,unsigned int y,unsigned int w,unsigned int h,SDL_Color color = {0xff,0xff,0xff})
		{
			this->id = id;
			this->rect.x = x;
			this->rect.y = y;
			this->rect.w = w;
			this->rect.h = h;
			this->color = color;
		}
		inline void move(Tile* next)
		{
			swap(this->rect.x,next->rect.x);
			swap(this->rect.y,next->rect.y);
		}

		bool check_bounds(int x, int y);

};


bool Tile::check_bounds(int x,int y)
{
	unsigned int rx = this->rect.x;
	unsigned int ry = this->rect.y;
	unsigned int rw = this->rect.w;
	unsigned int rh = this->rect.h;

	if ( rx <= x && rx+rw >= x)
		if( ry <= y && ry+rh >= y)
			return true;
	return false;
}



class Puzzle{
	private:
		SDL_Texture * texture;
		int findfree(Uint8 id);
		Tile * canvas;
	public:
		Tile **tiles;
		Puzzle();
		int loadImage(SDL_Renderer * renderer,const char * filename);	
		void draw(SDL_Renderer *renderer);
		void reset();
		void handleclick(int id);

		~Puzzle()
		{
			free(this->tiles);
			SDL_DestroyTexture(this->texture);
		}

};

void Puzzle::reset()
{
	for(int i = 0 ; i < 8 ; i ++ )
	{
		swap(this->tiles[i],this->tiles[i+1]);
	}
}

int Puzzle::findfree(Uint8 id)
{
	//Uint8 neighbours[4] = {0}; // { left, right, top, bottom } 
	vector<Uint8> neighbours;
	
	if(id+1 <= 8 && (id) % 3 != 0)
	{
		neighbours.push_back(id+1);
	}
	if(id-1 >= 0 && (id) % 3 != 0)
	{
		neighbours.push_back(id-1);
	}

	if(id + 3 <= 8)
		neighbours.push_back(id+3);
	if(id - 3 >= 0)
		neighbours.push_back(id-3);

	for (int i = 0 ; i < neighbours.size(); i++)
	{
		if(this->tiles[neighbours[i]]->empty)
		{
			return neighbours[i];
		}
	}
	return -1;
}
void Puzzle::handleclick(int id)
{
	int empty = this->findfree(id);
	if(empty > -1)
	{
		this->tiles[id]->move(this->tiles[empty]);
		swap(this->tiles[id],this->tiles[empty]);
	}
}

int Puzzle::loadImage(SDL_Renderer * renderer,const char * filename)
{
	SDL_Surface * img = IMG_Load(filename);
	if(!img)
	{
		cerr << "Unable to open image "<<filename<<endl;
		return -1;
	}
	this->texture = SDL_CreateTextureFromSurface(renderer,img);
	if(!this->texture)
	{
		cerr << "ERROR: "<<SDL_GetError()<<endl;
		return -1;
	}
	cout << "Loaded image "<<filename << " at "<<this->texture<<endl;

	
	// first load up the canvas
		
	this->canvas->src.w = img->w;
	this->canvas->src.h = img->h;
	this->canvas->src.x = 0;
	this->canvas->src.y = 0;

	int x = 0,y = 0;
	int c = 0;
	for(int i = 0 ;i < 8; i++)
	{
		this->tiles[i]->src.w = img->w/3;
		this->tiles[i]->src.h = img->h/3;
		this->tiles[i]->src.x = x;
		this->tiles[i]->src.y = y;
		x += img->w/3;
		if ( c == 2 )
		{
			x = 0;
			y += img->h/3;
			c = 0;
		}else
		{
			c++;
		}
	}
	
	free(img);

	return 0;

}

Puzzle::Puzzle()
{
	srand(time(NULL));
	this->tiles = (Tile **)malloc(sizeof(Tile) * 9);
	this->canvas = new Tile(0xff,20,20,200,200);
	int x = 10;
	int y = 240;
	for(int i = 0; i < 9; i ++)
	{
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;
		SDL_Color color;
		color.r = r;
		color.g = g;
		color.b = b;

		this->tiles[i] = new Tile(i,x,y,100,100,color);
		if( x >= 110 * 2)
		{
			x = 10;
			y += 110;
		}
		else
			x += 110;
	}
	this->tiles[8]->empty = true;

}


void Puzzle::draw(SDL_Renderer* renderer)
{
	
	for(int i = 0; i < 9; i++)
	{
			
		int r = this->tiles[i]->color.r;
		int g = this->tiles[i]->color.g;
		int b = this->tiles[i]->color.b;
		if(this->tiles[i]->empty)
		{
			SDL_SetRenderDrawColor(renderer,r,g,b,0xff);
			SDL_RenderFillRect(renderer,&this->tiles[i]->rect);
		}
		else
		{
			SDL_Rect src,dest;
			src = this->tiles[i]->src;
			dest = this->tiles[i]->rect;
			SDL_RenderCopy(renderer,this->texture,&src,&dest);
			
		}
	}
	SDL_RenderCopy(renderer,this->texture,&this->canvas->src,&this->canvas->rect);

}

