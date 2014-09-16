#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "background.h"
#include "render.h"
#include "player.h"
#include "asset.h"
#include "point.h"

#define KEY_SPACE 0x20
#define KEY_LEFT  97
#define KEY_RIGHT 100
#define KEY_RUN 115

class Level {
public:
	Level(Render *render);
	virtual ~Level();

	void load();
	void update();
    void onkeypress(int key);
    void onkeyup(int key);
    void updateinput();
	
private:
	Background *background;	
	Render *render;
	Player *player;

    Point position;
    Point velocity;
    float gravity;
	unsigned direction;
    unsigned jumping;
    unsigned running;
    unsigned idle;
    
    unsigned keyStates[256+1];
};

#endif