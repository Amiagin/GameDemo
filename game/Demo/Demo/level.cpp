#include "level.h"

Level::Level(Render *render) {
	this->render = render;
}

Level::~Level() {	
}

void Level::load() {
    int index = 0;
	background = new Background(render);
	background->add(LOCATE_ASSET_FILE(background/background1.png));
  
	player = new Player(render);
	player->load(0,LOCATE_ASSET_FILE(player/mario1_left.png));
	player->load(0,LOCATE_ASSET_FILE(player/mario2_left.png));
	player->load(0,LOCATE_ASSET_FILE(player/mario3_left.png));

	player->load(1,LOCATE_ASSET_FILE(player/mario1_right.png));
	player->load(1,LOCATE_ASSET_FILE(player/mario2_right.png));
	player->load(1,LOCATE_ASSET_FILE(player/mario3_right.png));
    
    player->load(2,LOCATE_ASSET_FILE(player/mario_jump.png));
    
    player->load(3,LOCATE_ASSET_FILE(player/mario1_left.png));
    
	this->position.x = (screenWidth*0.09f);
	this->position.y = 0;
    
    this->velocity.x = 0.95f;
    this->velocity.y = 0.0f;
    
    this->gravity = 0.3f;
    
	this->direction = 1;
    this->jumping = 0;
    this->idle = 0;
    this->running = 0;
    
    background->setDirection(this->direction);
    
    while (index < sizeof(this->keyStates)) {
        this->keyStates[index] = 0;
        index++;
    }
}

void Level::update() {
    if (!this->idle) {
	    player->draw(this->direction,this->position.x,this->position.y);
    } else {
        player->draw(3,this->position.x,this->position.y);
    }
    
	background->draw();
    
    if (this->jumping) {
        this->velocity.y += gravity;
        this->position.x += this->velocity.x;
        this->position.y += this->velocity.y;
        
        if (this->position.y > (screenHeight * 0.20f)) {
            this->position.y = 0;
            this->velocity.y = 0;
            this->jumping = 0;
        }
        
        if ((this->position.y < ((screenHeight * 0.20f) * 0.004f)) || (this->position.y > ((screenHeight * 0.20f) * 0.702f))) {
            this->velocity.y *= 0.6f;
        }
    }

    this->updateinput();
}

void Level::onkeypress(int key) {
    this->keyStates[key] = 1;
}

void Level::onkeyup(int key) {
    this->keyStates[key] = 0;
}

void Level::updateinput() {    
    if (this->keyStates[KEY_SPACE] == 1 && !this->jumping) {
        this->jumping = 1;
        this->velocity.y = 0.006f;
    }
    
    if (this->keyStates[KEY_RUN] == 1 && !this->running) {
        this->running = 1;
        this->velocity.x = (0.95f*16);
    } else {
        this->running = 0;
        this->velocity.x = 0.95f;
    }
    
    if (this->keyStates[KEY_LEFT] || this->keyStates[KEY_RIGHT]) {
        if (this->keyStates[KEY_LEFT] == 1) {
            this->direction = 0;
            background->setDirection(this->direction);
        } else if (this->keyStates[KEY_RIGHT] == 1) {
            this->direction = 1;
            background->setDirection(this->direction);
        }
        
        if (!background->scrollEndReached()) {
            background->scroll(this->velocity.x);
        } else {
            if (this->direction == 0) {
                this->position.x -= this->velocity.x;
                if (this->position.x <= (screenWidth*0.01f)) {
                    this->position.x += this->velocity.x;
                }
            } else {
                this->position.x += this->velocity.x;
                if (this->position.x >= (screenWidth*0.97f)) {
                    this->position.x -= this->velocity.x;
                }
            }
            
            printf("%0.2f\n",this->position.x);
        }
    }
}