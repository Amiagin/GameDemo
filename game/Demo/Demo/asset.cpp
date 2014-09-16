#include "asset.h"

Asset::Asset(Render *render) {
	this->render = render;
}

Asset::~Asset() {
}

void Asset::load(const char *filename) {
	texture = new Texture();
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
    
    this->bounds.x = 0;
    this->bounds.y = 0;
    
    this->bounds.width = (texture->getHeight()*scaleX);
    this->bounds.height = (texture->getWidth()*scaleY);
}

void Asset::draw(int x, int y) {
    
	render->push();
    render->draw(texture,x,y);
	render->pop();

    this->bounds.x = x;
    this->bounds.y = y;
}

Rect Asset::getBounds() {
    return this->bounds;
}