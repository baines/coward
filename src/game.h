#ifndef _GAME_H_
#define _GAME_H_
#include "gamestate.h"
#include "audio.h"
#include "player.h"
#include "text.h"
#include <list>

class Player;
class Enemy;
class Powerup;

class Game : public Gamestate {
	public:
		Game(StateMgr& mgr, int lvl, int prevhp);
		~Game();
		void update(Input& input, Uint32 delta);
		void draw(std::vector<uint16_t>& gfx);
	private:
		int timer, spawn_timer, door_timer, hurt_timer, invuln_timer, pwr_timer, lvl;
		Sound hurt_snd, door_snd, exit_snd, pwr_snd, zdie;
		Texture tex;
		Player player;
		std::list<Enemy*> enemies;
		typedef std::list<Enemy*>::iterator enemy_it;
		std::list<Sprite*> grid;
		typedef std::list<Powerup*>::iterator pwr_it;
		std::list<Powerup*> powerups;
		typedef std::list<Sprite*>::iterator sprite_it;
		Sprite bar_bg, door, hp;
		Text door_text;
		bool door_open, invuln;
};

#endif
