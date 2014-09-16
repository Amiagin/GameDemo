#ifndef __SCENE_H__
#define __SCENE_H__

#include "level.h"
#include "render.h"

class Scene {
public:
	Scene();
	virtual ~Scene();

	void load();
	void update();
    void onkeypress(int key);
    void onkeyup(int key);

private:
	Level *level;
	Render *render;
};

#endif