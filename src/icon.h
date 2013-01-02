#include <cassert>
#include <SDL/SDL.h>
#include "icon.xpm"

static const int ICON_W = 32;
static const int ICON_H = 32;

void parseColour(unsigned int* colour, const char* str){
	if(str[0] == 'o'){
		*colour = 0;
	} else {
		unsigned int n = 0;
		sscanf(str, "%x", &n);
		*colour = (n << 8) | 0xFF;
	}
}

void setIcon(void){
	unsigned int* pixels = new unsigned int[32*32];
	int w, h, c, d;
	sscanf(icon_xpm[0], "%d %d %d %d", &w, &h, &c, &d);

	//assert(d == 1);
	//assert(w <= ICON_W);
	//assert(h <= ICON_H);

	unsigned int* colours = new unsigned int[c*2];	

	for(int i=0; i<c; ++i){
		colours[i*2] = icon_xpm[i+1][0];
		parseColour(colours+1+i*2, icon_xpm[i+1]+5);
	}

	int pw = ICON_W / w, ph = ICON_H / h;

	for(int i=0; i<ICON_H; ++i){
		for(int j=0; j<ICON_W; ++j){
			char p = icon_xpm[1+c+i/ph][j/pw];
			for(int k = 0; k < c*2; k+=2){
				if(p == (unsigned char)colours[k])
					pixels[(i*ICON_W)+j] = colours[k+1];
			}
		}
	}

	SDL_Surface* s = SDL_CreateRGBSurfaceFrom(
		pixels, ICON_W, ICON_H, 32, ICON_W * 4, 
		0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF
	);
	
	SDL_WM_SetIcon(s, NULL);
	SDL_FreeSurface(s);
	delete [] colours;
	delete [] pixels;
}
