#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "glcontext.h"
#include "vec.h"
#include <vector>

typedef struct Vertex{
	short vertx, verty;
	short textx, texty;
	unsigned int texID;
} Vertex;

typedef struct {
	struct Vertex v[4];
} Vert4;

class Renderer {
public:
	static Renderer& get();
	void draw(std::vector<uint16_t>& indices);
	Vert4& addQuad(float x, float y, float w, float h, uint16_t* out);
	void delQuad(uint16_t index){ gfx.pop(index/4); }
	void toggleFullscreen(void);
	void toggleBorder();
	int vsync;
	Vec<Vert4> gfx;
protected:
	Renderer(int w, int h, const char* caption);
	void reload(int w, int h, int flags);
	SDL_Surface* screen;
	int fullscreen_w, fullscreen_h, windowed_w, windowed_h;
};

#endif
