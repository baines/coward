#ifndef _TITLE_H_
#define _TITLE_H_
#include "gamestate.h"
#include "game.h"
#include "text.h"

class Title : public Gamestate {
	public:
		Title(StateMgr& mgr) : Gamestate(mgr), bg(NULL, 160, 120, 320, 240),
			title("title.png", 160, 120, 320, 240), thunder("thunder.wav"),
			myname(270, 8, 8, 8, "2011 Alex Baines"), ltimer(200+rand()%1000),
			ldist(0-rand()%2000){
			
		}
		void update(Input& input, Uint32 delta){
			ltimer -= delta;
			if(ltimer < ldist){
				thunder.play();
				ltimer = 4000 + rand()%15000;	
				ldist = 0 - rand()%2000;
			}
			if(input.keys[SDLK_SPACE]){
			    input.keys[SDLK_SPACE] = false;
			    input.keys[SDLK_RETURN] = false;
				statemgr.pop(1);
				statemgr.push(new Game(statemgr, 0, 200));
			}
		}
		void draw(std::vector<uint16_t>& gfx){
			if(ltimer < 0 && ltimer > -150) bg.draw(gfx);
			title.draw(gfx);
			myname.draw(gfx);
		}
	private:
		Sprite bg, title;
		Sound thunder;
		Text myname;
		int ltimer, ldist;
};

#endif
