#ifndef __ASSET_H__
#define __ASSET_H__

#include "texture.h"
#include "render.h"
#include "rect.h"
#include <vector>

class Render;

class Asset {
public:
	Asset(Render *render);
	virtual ~Asset();
    
	void load(const char *filename);
	void draw(int x, int y);
    
    Rect getBounds();
        
private:
	Texture *texture;
	Render *render;
    
    Rect bounds;
};

#endif