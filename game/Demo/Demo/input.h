#ifndef __GAME_INPUT_H__
#define __GAME_INPUT_H__

#include <stdio.h>
#include <stdlib.h>

class Input {
public:
	Input();
	virtual ~Input();
    
    void onkeypress(int key);
    void onkeyup(int key);
    void update();

private:
    unsigned keyStates[256];
};

#endif