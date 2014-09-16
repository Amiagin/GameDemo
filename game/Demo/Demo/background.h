#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "texture.h"
#include "render.h"
#include "rect.h"
#include <vector>

class Render;

class Background {
public:
	Background(Render *render);
	virtual ~Background();

	void add(const char *filename);
	void draw();
    void scroll(float value);
    void setDirection(unsigned direction);
    float getScrollX();
    Rect getBounds(int id);
    unsigned scrollEndReached();

private:
	std::vector<Texture *>textures;	
	Render *render;
    unsigned direction;
    float scrollX,scrollY;
};

#endif