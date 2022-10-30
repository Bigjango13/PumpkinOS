#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <common.h>

#define FB_WIDTH get_fb_width()
#define FB_HEIGHT get_fb_height()

// Inits the framebuffer, should be called before anything else
void fb_init();
int get_fb_width();
int get_fb_height();

// Draws a (x, y), attr is the color.
void drawPixel(int x, int y, unsigned int attr);
void drawRect(int x1, int y1, int x2, int y2, unsigned int attr, bool fill);
void drawCircle(int x0, int y0, int radius, unsigned int attr, bool fill);
void drawLine(int x1, int y1, int x2, int y2, unsigned int attr);
void drawTriangle(int x, int y, int hight, unsigned int attr, bool upsidedown);

void wait_msec(unsigned int n);
#define wait_sec(x) wait_msec(x * 1000000)

#ifdef __cplusplus
}
#endif
