#include <common.h>
#include <fb.h>

void main() {
    fb_init();

    // Helper vars to make code more readable
    // y1 is often used as hight (for drawTriangle) or radius (for drawCircle)
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    while (1) {
        // Bottom of pumkin skin
        drawRect(0, 0, FB_WIDTH, FB_HEIGHT, PUMPKIN_SKIN, true);
        // Mouth
        x0 = FB_WIDTH / 2;
        y0 = (FB_HEIGHT / 5) * 2;
        y1 = (FB_WIDTH / 5) * 2;
        drawCircle(x0, y0, y1, PUMPKIN_INTERIOR, true);
        y1 = y0 + (FB_HEIGHT / 10);
        drawRect(0, 0, FB_WIDTH, y1, PUMPKIN_SKIN, true);
        // Top tooth 1
        x0 = FB_WIDTH / 4;
        x1 = x0 + (FB_WIDTH / 10);
        y1 += (FB_HEIGHT / 10);
        drawRect(x0, y0, x1, y1, PUMPKIN_SKIN, true);
        // Top tooth 2
        x0 *= 3;
        x0 -= (FB_WIDTH / 10);
        x1 = x0 + (FB_WIDTH / 10);
        drawRect(x0, y0, x1, y1, PUMPKIN_SKIN, true);
        // Bottom tooth
        x1 = FB_WIDTH / 2;
        y1 = FB_HEIGHT;
        y0 = y1 - (FB_HEIGHT / 10);
        x0 = x1 - (FB_WIDTH / 10);
        x0 += (FB_HEIGHT / 20);
        x1 += (FB_HEIGHT / 20);
        drawRect(x0, y0, x1, y1, PUMPKIN_SKIN, true);
        // Eye 1
        x0 = FB_WIDTH / 4;
        y0 = (FB_HEIGHT / 10) * 2;
        y1 = FB_HEIGHT / 5;
        drawTriangle(x0, y0, y1, PUMPKIN_INTERIOR, false);
        drawCircle(x0, y0, y1 / 4, PUMPKIN_SKIN, true);
        // Eye 2
        x0 *= 3;
        drawTriangle(x0, y0, y1, PUMPKIN_INTERIOR, false);
        drawCircle(x0, y0, y1 / 4, PUMPKIN_SKIN, true);
        // Nose
        x0 = FB_WIDTH / 2;
        y0 = FB_HEIGHT / 2;
        y0 -= y1 / 2;
        drawTriangle(x0, y0, y1, PUMPKIN_INTERIOR, false);

        #ifdef REDRAW
        // Used for testing on diffrent sized monitors
        wait_sec(REDRAW);
        #else
        // Don't redraw, instead exit the loop
        break;
        #endif
    }

    while (1);
}
