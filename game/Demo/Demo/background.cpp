#include "background.h"

Background::Background(Render *render) {
	this->render = render;
}

Background::~Background() {
	textures.clear();
}

void Background::add(const char *filename) {
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
    textures.push_back(texture);
    
    this->scrollX = 0;
    this->scrollY = 0;
    this->direction = 0;
}

void Background::draw() {	
	unsigned long index = textures.size();
	render->push();	

	while (index > 0) {
		Texture *texture = textures.at(index-1);
	    render->draw(texture,this->scrollX,this->scrollY);
		index--;
	}
    
	render->pop();
}

void Background::scroll(float value) {
    if (this->direction == 1) {
        this->scrollX -= value;
    } else {
        this->scrollX += value;
    }
}

float Background::getScrollX() {
    return this->scrollX;
}

Rect Background::getBounds(int id) {
    Rect bounds;
    
    bounds.width = textures.at(id)->getWidth()*scaleX;
    bounds.height = textures.at(id)->getHeight()*scaleY;
    bounds.x = 0;
    bounds.y = 0;
    
    return bounds;
}

unsigned Background::scrollEndReached() {
    if (this->direction == 1) {
        if (((textures.at(0)->getWidth()*scaleX)+this->scrollX) <= screenWidth) {
            return 1;
        }
    } else {
        if (this->scrollX >= 0) {
            return 1;
        }
    }
    return 0;
}

void Background::setDirection(unsigned int direction) {
    this->direction = direction;
}