#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "glcontext.h"
#include "util.h"
#include "audio.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <map>

class Texture {
public:
	Texture(const char* name){
		id = name == NULL ? getDefaultTexture() : util::cache<GLuint>(getmap(), name, load, "./data/img/");
	}
	static void reload(){
		TexMap& m = getmap();
		for(TexMap::const_iterator i = m.begin(), j = m.end(); i != j; ++i){
			std::string s = "./data/img/" + i->first;
			load2(s.c_str(), i->second);
		}
	}
	GLuint id;
private:
	typedef std::map<std::string, GLuint> TexMap;
	static GLuint getDefaultTexture(){
		static GLuint t = 0;
		if(t == 0) t = load(NULL);
		return t;
	}
	static TexMap& getmap(){
		static TexMap map;
		return map;
	}
	static GLuint load(const char* path){
		GLuint tex;
		gl.GenTextures(1, &tex);
		return load2(path, tex);
	}			
	static GLuint load2(const char* path, GLuint texture){
		SDL_Surface* surface;
		if(!path){
			uint32_t p = 0xffffffffUL;
			surface = SDL_CreateRGBSurfaceFrom(
				&p, 1, 1, 0, 4,	0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff
			);
		} else {
			surface = IMG_Load(path);
		}

		if (!surface){
			fprintf(stderr, "%s missing or corrupt.\n", path);
			exit(1);
		}

		gl.BindTexture(GL_TEXTURE_2D, texture);
		gl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		gl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		gl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		gl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		gl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		gl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		gl.TexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, 
			GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	
		SDL_FreeSurface(surface);	
		return texture;
	}
};
#endif
