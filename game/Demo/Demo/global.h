#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#define SCALE_FACTOR 0.5f
#define SCREEN_WIDTH 1136
#define SCREEN_HEIGHT 640

#define ASSET_FOLDER    "../../../assets/"
#define LOCATE_ASSET_FILE(name)    ASSET_FOLDER #name

/*
     1st Gen, 3G & 3GS    = 320x480
     4 & 4S               = 640x960
     5, 5C & 5S           = 640x1136
     6                    = 750x1334
     6 Plus               = 1080x1920
 */

extern int screenWidth, screenHeight;
extern float scaleX, scaleY;

#endif