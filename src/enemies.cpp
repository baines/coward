#include "enemy.h"
#include <cmath>

Zombie::Zombie(int x, int y) : Enemy(x, y, 8, 8, 4, 8), die("zdie.ogg") {
	speed = (rand()%100 / 120.0f) + 0.1f;
	setFrame(1, 0);
	ttl = 2000 + rand()% 4000;
	dead = false;
}

void Zombie::update(float playerx, float playery, float delta) {

	ttl -= delta;

	if(ttl > 0){
		float f = sqrt(pow(playerx - x, 2) + pow(playery - y, 2));
		x += speed * (delta / 16.0f) * (playerx - x) / f;
		y += speed * (delta / 16.0f) * (playery - y) / f;
	} else if(!dead){
		dead = true;
		die.play();
		setFrame(2,0);
	}

}

Bouncer::Bouncer(int x, int y) : Enemy(x, y, 4, 4, 8, 16), boing("boing.ogg") {
	float rot = (rand()%628) / 100.0f;
	float spd = 0.35f+(rand()%20) / 10.0f;

	xVel = spd * sin(rot);
	yVel = spd * cos(rot);

	setFrame(6, 0);
}

void Bouncer::update(float playerx, float playery, float delta) {
	x += xVel * (delta / 16.0f);
	y += yVel * (delta / 16.0f);
	
	if(x < 4.0f || x > 316.0f){
		x = (x < 4.0f) ? 4.1f : 315.0f;
		xVel *= -1.0f;
		boing.play();
	}
	if(y < 20.0f || y > 236.0f){
		y = (y < 20.0f) ? 21.0f : 235.0f;
		yVel *= -1.0f;
		boing.play();
	}
}

Giant::Giant(int x, int y) : Zombie(x, y) {
	speed = 0.05f + rand()%20 / 20.0f;
	grow_timer = 1000 + rand()%2000;
	setFrame(2, 2);
}

void Giant::update(float playerx, float playery, float delta){
	Zombie::update(playerx, playery, delta);
	ttl = 999;
	grow_timer -= delta;
	if(grow_timer < 0){
		w+=2;
		h+=2;
		grow_timer = 1000 + rand()%2000;
	}

}


