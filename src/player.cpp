#include "player.h"

Player::Player(const Texture& tex) : Sprite(tex, 160, 120, 8, 8, 4, 8) {
	xVel = yVel = 0;
}

void Player::update(Input& input, Uint32 delta){
	if(input.keys[SDLK_LEFT]) xVel -= delta;
	else if(input.keys[SDLK_RIGHT]) xVel += delta;
	else if(xVel != 0){
		int i = util::min(abs(xVel), delta);
		xVel += i * ((xVel < 0) - (xVel > 0));
	}

	if(input.keys[SDLK_UP]) yVel -= delta;
	else if(input.keys[SDLK_DOWN]) yVel += delta;
	else if(yVel != 0){
		int i = util::min(abs(yVel), delta);
		yVel += i * ((yVel < 0) - (yVel > 0));
	}
	
	xVel = util::max(-128, util::min(128, xVel));
	yVel = util::max(-128, util::min(128, yVel));

	x = util::max(util::min(x + (((float)xVel * delta) / 1024.0f), 316.0f), 4.0f);
	y = util::max(util::min(y + (((float)yVel * delta) / 1024.0f), 236.0f), 20.0f);
}

