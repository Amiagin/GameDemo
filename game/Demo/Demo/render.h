#ifndef __RENDER_H__
#define __RENDER_H__

#include "global.h"
#include "texture.h"

#define ON 1
#define OFF 0

class Render {
public:
	Render();
	virtual ~Render();

	void draw(Texture *texture,GLfloat x, GLfloat y);
	void push();
	void pop();

	void blend(unsigned state);
};

#endif