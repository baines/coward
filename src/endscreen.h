#ifndef _ENDSCREEN_H_
#define _ENDSCREEN_H_
#include "gamestate.h"
#include "sprite.h"
#include "title.h"

class Endscreen : public Gamestate {
	public:
		Endscreen(StateMgr& mgr, int score) : Gamestate(mgr), tex("title.png"),
			title(tex, 160, 120, 256, 128, 1, 2), timer(0), 
			stext(164, 106, 16, 16, "%d.%2d", score / 1000, (score/10) % 100) {
			title.setFrame(0, 1);
		}
		void update(Input& input, Uint32 delta){
			if(timer > 10000 || input.keys[SDLK_SPACE]){
			    input.keys[SDLK_SPACE] = false;
				statemgr.pop(1);
				statemgr.push(new Title(statemgr));
			}
			timer += delta;
		}
		void draw(std::vector<uint16_t>& gfx){
			title.draw(gfx);
			stext.draw(gfx);
		}
	private:
		Texture tex;
		Sprite title;
		unsigned int timer;
		Text stext;
};

#endif
