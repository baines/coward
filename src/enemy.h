#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "sprite.h"
#include "audio.h"

class Enemy : public Sprite {
	public:
		Enemy(int x, int y, int w, int h, int xseg, int yseg) 
			: Sprite(tex(), x, y, w, h, xseg, yseg){};
		virtual void update(float playerx, float playery, float delta) = 0;
	protected:
		static Texture& tex(){
			static Texture tex("sprites.png");
			return tex;
		}
};

class Zombie : public Enemy /*Number 1*/ {
	public:
		Zombie(int x, int y);
		virtual void update(float playerx, float playery, float delta);
	protected:
		int ttl;
		float speed;
		bool dead;
		Sound die;
};

class Bouncer : public Enemy {
	public:
		Bouncer(int x, int y);
		void update(float playerx, float playery, float delta);
	private:
		float xVel;
		float yVel;
		Sound boing;
};

class Giant : public Zombie {
	public:
		Giant(int x, int y);
		void update(float playerx, float playery, float delta);
	private:
		int grow_timer;
};

#endif
