#ifndef _POWERUP_H_
#define _POWERUP_H_
#include "sprite.h"

enum { POWERUP_HP, POWERUP_SUPER };

class Powerup : public Sprite {
	public:
		Powerup(Texture& tex, int type, int x, int y) : Sprite(tex, x, y, 8, 8, 4, 8){
			this->type = type;			
			if(type == POWERUP_HP){
				setFrame(3, 1);
			} else {
				setFrame(3, 2);
			}
		}
	int type;
};

#endif

