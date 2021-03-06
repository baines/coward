#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include "input.h"
#include "statemgr.h"
#include "sprite.h"

class Gamestate {
public:
	Gamestate(StateMgr& mgr) : statemgr(mgr){};
	virtual ~Gamestate(){};
	virtual void update(Input& input, Uint32 delta){};
	virtual void draw(std::vector<uint16_t>& indices){};
protected:
	StateMgr& statemgr;
};

#endif
