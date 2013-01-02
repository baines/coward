#ifndef _GL_CONTEXT_H_
#define _GL_CONTEXT_H_
#define _GL_STRING(name) #name
#define _GL(name) _GL_STRING(gl##name)
#include <SDL/SDL_opengl.h>
#include "opengl.h"
#include "util.h"
#include <SDL/SDL.h>

class GLContext {
public:
	int initial_w, initial_h;
	GLContext() : initial_w(320), initial_h(240)
		#define _GL_FN(type, name, args) \
			, name(0)
		#include "opengl.h"
		#undef _GL_FN
	{}
	void createContext(int w, int h){
		loadAllFuncs();			
		MatrixMode(GL_PROJECTION);
		LoadIdentity();
		Ortho(0, initial_w, initial_h, 0, -1, 1);
        int scale = util::min(h / initial_h, w / initial_w);
        int xOff = (w - (initial_w * scale)) / 2;
        int yOff = (h - (initial_h * scale)) / 2;
        Viewport(xOff, yOff, initial_w * scale, initial_h * scale);
		MatrixMode(GL_TEXTURE);
		LoadIdentity();
		Scalef(1.0f/128.0f, 1.0f/128.0f, 1.0f);
		MatrixMode(GL_MODELVIEW);
		Enable(GL_TEXTURE_2D);
		Enable(GL_BLEND);
		FrontFace(GL_CW);
		Enable(GL_CULL_FACE);
		BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		EnableClientState(GL_VERTEX_ARRAY);
		EnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	bool loadFunction(const char* name, void** ptr){
		*ptr = SDL_GL_GetProcAddress(name);
		if(*ptr){
			return true;
		} else {
			printf("OpenGL function %s not available.\n", name);
			return false;
		}
	}
			
	bool loadAllFuncs(){
		bool retval = true;
		#define _GL_FN(type, name, args) \
			retval = retval && loadFunction(_GL(name), (void**)&name);
		#include "opengl.h"
		#undef _GL_FN
		return retval;
	}

	#define _GL_FN(type, name, args) \
		name##_p name;
	#include "opengl.h"
	#undef _GL_FN
};

extern GLContext gl;

#endif
