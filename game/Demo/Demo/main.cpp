//
//  main.cpp
//  Demo
//
//  Created by Christopher Del Rosario on 9/10/14.
//  Copyright (c) 2014 None. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if defined(__APPLE__)
#    include <OpenGL/gl.h>
#    include <OpenGL/glu.h>
#    include <GLUT/glut.h>
#else
#    pragma comment(lib,"glut32.lib")
#    include <GL/glut.h>
#endif

#include "global.h"
#include "scene.h"

int screenWidth = 0;
int screenHeight = 0;

float scaleX = 0;
float scaleY = 0;

Scene *scene;

void init() {
    
	scaleX = (float)((float)screenWidth/SCREEN_WIDTH);
	scaleY = (float)((float)screenHeight/SCREEN_HEIGHT);
    
	scene = new Scene();
	scene->load();
    
	glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LEQUAL);
    glEnable(GL_BGR_EXT);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER, 0.1);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // 85 197 245
    
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    
    glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	scene->update();
    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_TEXTURE_2D);
    
	glFlush();
	glutSwapBuffers();
}

void reshape(int width, int height) {
	glViewport(0, 0, screenWidth, screenHeight);
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void update() {
	glutPostRedisplay();
}

void keypressed(unsigned char key, int x, int y) {
    scene->onkeypress(key);
}

void keyup(unsigned char key, int x, int y) {
    scene->onkeyup(key);
}

void spkeypressed(int key, int x, int y) {
    scene->onkeypress(key);
}

void spkeyup(int key, int x, int y) {
    scene->onkeyup(key);
}

int main(int argc, char *argv[]) {
    
	screenWidth = SCREEN_WIDTH*SCALE_FACTOR;
	screenHeight = SCREEN_HEIGHT*SCALE_FACTOR;
    
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(screenWidth,screenHeight);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Clip");
    
	init();
    
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(update);
    
	glutKeyboardFunc(keypressed);
	glutKeyboardUpFunc(keyup);
    
    glutSpecialFunc(spkeypressed);
    glutSpecialUpFunc(spkeyup);
    
	glutMainLoop();
	return 0;
}