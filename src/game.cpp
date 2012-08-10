#include "game.h"
#include "player.h"
#include "enemy.h"
#include "powerup.h"
#include "endscreen.h"
#include <cmath>
#include "audio.h"
#include <algorithm>

Game::Game(StateMgr& mgr, int lvl, int prevhp) : Gamestate(mgr), tex("sprites.png"), lvl(lvl), timer(0), 
	door_open(false), invuln(false), spawn_timer(rand()%1000), invuln_timer(0), 
	pwr_timer(10000 + rand()%20000), door_timer(10000 + 5000 * lvl), hurt_timer(0),
	hp(tex, 3+ (prevhp /2), 8, prevhp, 8, 4, 8), bar_bg(tex, 160, 8, 322, 16, 4, 8),
	door(tex, 20+rand()%300, 30+rand()%200, 16, 16, 4, 8),
	door_text(270, 8, 16, 16, "%02d:%02d:%02d", 0, 0, 0), hurt_snd("hurt.wav"), 
	door_snd("door.wav"), exit_snd("exit.wav"), pwr_snd("powerup.wav"), zdie("zdie.wav"), player(tex){
	
	hp.setFrame(2, 1);
	door.setFrame(0, 2);
	bar_bg.setFrame(1, 1);
	
	int px = rand()%2, py = 2 + rand()%2;
	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 7; ++j){
			grid.push_back(new Sprite(tex, 32 * i + 16, 32 * j + 32, 32, 32, 2, 4));
			grid.back()->setFrame(px, py);
		}
	}
}

Game::~Game(){
	std::for_each(grid.begin(), grid.end(), util::deleter());
	std::for_each(powerups.begin(), powerups.end(), util::deleter());
	std::for_each(enemies.begin(), enemies.end(), util::deleter());
}

void Game::update(Input& input, Uint32 delta){
	timer += delta;
	if(door_timer > 0){ 
		door_timer -= delta;
	} else if(!door_open) {
		door_timer = 0;
		door.setFrame(1, 2);
		door_open = true;
		door_snd.play();
	}
	player.update(input, delta);
	
	if(invuln_timer > 0){
		invuln_timer -= delta;
	} else if(invuln) {
		player.setFrame(0, 0);
		invuln = false;
	}

	door_text.update("%02d:%02d:%02d", door_timer / 60000, (door_timer / 1000) % 60, (door_timer % 1000) / 10);
	
	for(enemy_it i = enemies.begin(), j = enemies.end(); i != j; ++i){
		(*i)->update(player.x, player.y, delta);
		if(Sprite::collision(&player, (*i))){
			if(invuln){
				delete (*i);
				i = --enemies.erase(i);
				zdie.play();
			} else {
				player.setFrame(0, 1);
				float dmg = delta / 16.0f;
				hp.w-= dmg * 2.0f;
				hp.x-= dmg;
				if(hurt_timer <= 0) hurt_snd.play();
				hurt_timer = 100;
			}
		}
	}

	if(hp.w <= 0){
		statemgr.pop(1);
		statemgr.push(new Endscreen(statemgr, (10000 + lvl * 5000) * (lvl+1) - door_timer));
	} else if(door_open && Sprite::collision(&player, &door)){
		exit_snd.play();
		statemgr.pop(1);		
		statemgr.push(new Game(statemgr, ++lvl, hp.w));
	}

	if(pwr_timer < 0){
		if(!door_open) powerups.push_back(new Powerup(tex, rand()%2, 20+rand()%300, 30+rand()%200));
		pwr_timer = 10000 + rand()%20000;
	} else {
		pwr_timer -= delta;
	}

	for(pwr_it i = powerups.begin(), j = powerups.end(); i != j; ++i){
		if(Sprite::collision(&player, (*i))){
			if((*i)->type == POWERUP_HP){
				hp.w = util::min(200.0f, hp.w + 10);
				hp.x = hp.w / 2 + 3;
			} else if((*i)->type == POWERUP_SUPER){
				invuln_timer = 4000;
				invuln = true;
				player.setFrame(3, 3);
				hurt_timer = 0;
			}
			pwr_snd.play();
			delete (*i);
			i = --powerups.erase(i);
		}
	}
	
	if(hurt_timer > 0){
		hurt_timer -= delta;
		if(hurt_timer <= 0) player.setFrame(0, 0);
	}

	if(timer > spawn_timer){
		int enemy_type = rand()%20;
		float dx, dy;
		if(rand()%2){
			dx = (rand()%2) ? 340 : -20;
			dy = (rand()%240);
		} else {
			dx = (rand()%320);
			dy = (rand()%2) ? 260 : -20;
		}	
		if(enemy_type > 5){
			enemies.push_back(new Zombie(dx, dy));
		} else if(enemy_type < 3 && lvl > 1){
			enemies.push_back(new Bouncer(20+rand()%300, 30+rand()%200));
		} else if(enemy_type == 4 && lvl > 3){

			enemies.push_back(new Giant(dx, dy));
		}
		timer = 0;
		spawn_timer = 200 + rand()%2000 * util::max(1.0f / (lvl+1), 0.05f);
	}
}

void Game::draw(std::vector<uint16_t>& gfx){
	util::forEach(grid.begin(), grid.end(), &Sprite::draw, gfx);
	util::forEach(powerups.begin(), powerups.end(), &Sprite::draw, gfx);
	if(!door_open) door.draw(gfx);
	util::forEach(enemies.begin(), enemies.end(), &Sprite::draw, gfx);
	if(door_open) door.draw(gfx);
	player.draw(gfx);
	bar_bg.draw(gfx);
	hp.draw(gfx);
	door_text.draw(gfx);
}
