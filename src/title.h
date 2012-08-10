#ifndef _TITLE_H_
#define _TITLE_H_
#include "gamestate.h"
#include "game.h"
#include "text.h"

class Title : public Gamestate {
	public:
		Title(StateMgr& mgr) : Gamestate(mgr), tex("title.png"), 
		title(tex, 160, 120, 256, 128, 1, 2),
		myname(270, 8, 8, 8, "2011 Alex Baines"){}
		void update(Input& input, Uint32 delta){
			if(input.keys[SDLK_SPACE]){
			    input.keys[SDLK_SPACE] = false;
			    input.keys[SDLK_RETURN] = false;
				statemgr.pop(1);
				statemgr.push(new Game(statemgr, 0, 200));
			}
		}
		void draw(std::vector<uint16_t>& gfx){
			title.draw(gfx);
			myname.draw(gfx);
		}
	private:
		Texture tex;
		Sprite title;
		Text myname;
};

#endif
