#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#define PNG_NO_STDIO

#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#if defined(__APPLE__)
#   include <GLUT/glut.h>
#else
#    pragma comment(lib,"glut32.lib")
#    pragma comment(lib,"libpng.lib")
#    include <GL/glut.h>
#endif

class Texture {
public:
	Texture();
	virtual ~Texture();

	void load(const char *filename);

	GLuint getId();
	int getWidth();
	int getHeight();

	void load_png(const char *filename);

	void destroy();

private:
	unsigned char *png_image_buf;
	int png_image_width, png_image_height;
	GLuint texture_id;

public:
	GLfloat vtx[12];
	GLfloat coords[8];
	int size;
};

#endif