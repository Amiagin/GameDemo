#include "player.h"

Player::Player(Render *render) {
	this->render = render;
	this->frameCount = 0.0f;
	this->frameID = 0;
}

Player::~Player() {
    textures[0].clear();
	textures[1].clear();
}

void Player::load(int id,const char *filename) {
	Texture *texture = new Texture();	
	texture->load(filename);

    memset(texture->vtx,0,sizeof(GLfloat)*12);

    texture->vtx[1] = (texture->getHeight()*scaleY);
    texture->vtx[3] = (texture->getWidth()*scaleX);

    texture->vtx[4] = texture->vtx[1];
    texture->vtx[9] = texture->vtx[3];
	
    texture->coords[0] = 0.0f;
    texture->coords[1] = 0.0f;

    texture->coords[2] = 1.0f;
    texture->coords[3] = 0.0f;

    texture->coords[4] = 0.0f;
    texture->coords[5] = 1.0f;

    texture->coords[6] = 1.0f;
    texture->coords[7] = 1.0f;

    texture->size = 12;
    textures[id].push_back(texture);
        
    this->bounds.x = 0;
    this->bounds.y = 0;
    this->bounds.width = (texture->getWidth()*scaleX);
    this->bounds.height = (texture->getHeight()*scaleY);
}

void Player::draw(int id,float x, float y) {
	render->push();	

	if (this->frameCount > 5.0f) {
	    if (++this->frameID >= textures[id].size()) {
			this->frameID = 0;
		}
		this->frameCount = 0;
	}
    if (id < 4) {
	    Texture *texture = textures[id].at(this->frameID);
        if (texture != NULL) {
	        render->draw(texture,x,y);
        }
    }
    
	render->pop();

    this->bounds.x = x;
    this->bounds.y = y;

	this->frameCount+=0.8f;
}

Rect Player::getBounds() {
    return this->bounds;
}