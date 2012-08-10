#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "gamestate.h"

class Player : public Sprite {
	public:
		Player(const Texture& tex);
		void update(Input& input, Uint32 delta);
	private:
		int xVel, yVel;
};

#endif
