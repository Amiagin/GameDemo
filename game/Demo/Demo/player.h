#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "texture.h"
#include "render.h"
#include "rect.h"
#include <vector>

class Player {
public:
	Player(Render *render);
	virtual ~Player();
	void load(int id,const char *filename);
	void draw(int id,float x, float y);
    
    Rect getBounds();

private:
	std::vector<Texture*>textures[4];
	int textureCount;
	Render *render;
	float frameCount;
	unsigned int frameID;
    Rect bounds;
};

#endif