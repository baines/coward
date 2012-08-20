#include "statemgr.h"
#include "gamestate.h"
#include "input.h"
#include "util.h"

StateMgr::StateMgr() : states(), nextStates(), popAmount(0){}

StateMgr::~StateMgr(){
	for(state_itr i = nextStates.begin(), j = nextStates.end(); i != j; ++i)
		delete (*i);
	states.clear();
}

void StateMgr::update(Input& input, Uint32 delta){
	for(; popAmount > 0; --popAmount){
		delete states.back();
		states.pop_back();
	}
	
	if(!nextStates.empty()){
		for(state_itr i = nextStates.begin(), j = nextStates.end(); i != j; ++i)
			states.push_back(*i);
		nextStates.clear();
	}
	
	states.back()->update(input, delta);
}

void StateMgr::draw(std::vector<uint16_t>& indices){
	for(state_itr i = states.begin(), j = states.end(); i != j; ++i)
		(*i)->draw(indices);
}

void StateMgr::push(Gamestate* state){
	nextStates.push_back(state);
}

void StateMgr::pop(int amount){
	popAmount = util::min(amount, (int)states.size());
}

