#include "render.h"

Render::Render() {
}

Render::~Render() {
}

void Render::draw(Texture *texture, GLfloat x, GLfloat y) {
    if (texture != NULL) {
        glBindTexture(GL_TEXTURE_2D,texture->getId());
        
        glTranslatef(x,y,0.0);
        
        glTexCoordPointer(2,GL_FLOAT,0,texture->coords);
        glVertexPointer(3,GL_FLOAT,0,texture->vtx);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, texture->size);
    }
}

void Render::push() {
	glPushMatrix();
}

void Render::pop() {
	glPopMatrix();
}

void Render::blend(unsigned state) {
	if (state == ON) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	} else {
		glDisable(GL_BLEND);
	}
}