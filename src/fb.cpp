#include <fb.h>
#include <mb.h>

unsigned int width, height, pitch, isrgb;
unsigned char *fb;

void fb_init() {
    // Length of message in bytes
    mbox[0] = 35*4;
    mbox[1] = MAILBOX_REQUEST;

    // Tag identifier
    mbox[2] = MAILBOX_TAG_SETPHYWH;
    // Value size in bytes
    mbox[3] = 8;
    mbox[4] = 0;
    // Value(width)
    mbox[5] = 1920;
    // Value(height)
    mbox[6] = 1080;

    mbox[7] = MAILBOX_TAG_SETVIRTWH;
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = 1920;
    mbox[11] = 1080;

    mbox[12] = MAILBOX_TAG_SETVIRTOFF;
    mbox[13] = 8;
    mbox[14] = 8;
    // Value(x)
    mbox[15] = 0;
    // Value(y)
    mbox[16] = 0;

    mbox[17] = MAILBOX_TAG_SETDEPTH;
    mbox[18] = 4;
    mbox[19] = 4;
    // Bits per pixel
    mbox[20] = 32;

    mbox[21] = MAILBOX_TAG_SETPXLORDR;
    mbox[22] = 4;
    mbox[23] = 4;
    // RGB
    mbox[24] = 1;

    mbox[25] = MAILBOX_TAG_GETFB;
    mbox[26] = 8;
    mbox[27] = 8;
    // FrameBufferInfo.pointer
    mbox[28] = 4096;
    // FrameBufferInfo.size
    mbox[29] = 0;

    mbox[30] = MAILBOX_TAG_GETPITCH;
    mbox[31] = 4;
    mbox[32] = 4;
    // Bytes per line
    mbox[33] = 0;

    mbox[34] = MAILBOX_TAG_LAST;

    // Check call is successful and we have a pointer with depth 32
    if (mbox_call(MAILBOX_CH_PROP) && mbox[20] == 32 && mbox[28] != 0) {
        // Convert GPU address to ARM address
        mbox[28] &= 0x3FFFFFFF;
        // Actual physical width
        width = mbox[10];
        // Actual physical height
        height = mbox[11];
        // Number of bytes per line
        pitch = mbox[33];
        // Pixel order
        isrgb = mbox[24];
        fb = (unsigned char *)((long)mbox[28]);
    }
}

int get_fb_width()  { return width;  }
int get_fb_height() { return height; }

void drawPixel(int x, int y, unsigned int attr) {
    if (x <= width && y <= height) {
        int offs = (y * pitch) + (x * 4);
        *((unsigned int*)(fb + offs)) = attr;
    }
}

void drawRect(int x1, int y1, int x2, int y2, unsigned int attr, bool fill) {
    // Draws a rectangle
    int y = y1;

    while (y <= y2) {
        int x=x1;
        while (x <= x2) {
	        if ((x == x1 || x == x2) || (y == y1 || y == y2)) {
	            drawPixel(x, y, attr);
	        } else if (fill) {
	            drawPixel(x, y, attr);
            }
            x++;
       }
       y++;
    }
}

void drawLine(int x1, int y1, int x2, int y2, unsigned int attr) {
    // Draws a line
    int dx, dy, p, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    x = x1;
    y = y1;
    p = (2 * dy) - dx;

    while (x < x2) {
       if (p >= 0) {
          drawPixel(x, y, attr);
          y++;
          p = p + (2 * dy) - (2 * dx);
       } else {
          drawPixel(x, y, attr);
          p = p + 2 * dy;
       }
       x++;
    }
}

void drawTriangle(int x, int y, int extent, unsigned int attr, bool upsidedown) {
    for (int i = 0; i <= extent; i++) {
        if (upsidedown) {
            drawLine(x - ((int) i / 2), y - i, x + ((int) i / 2), y - i, attr);
        } else {
            drawLine(x - ((int) i / 2), y - (extent - i) + 1, x + ((int) i / 2), y - (extent - i) + 1, attr);
        }
    }
}

void drawCircle(int x0, int y0, int radius, unsigned int attr, bool fill) {
    // Draws a circle
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
    	if (fill) {
    	   drawLine(x0 - y, y0 + x, x0 + y, y0 + x, attr);
    	   drawLine(x0 - x, y0 + y, x0 + x, y0 + y, attr);
    	   drawLine(x0 - x, y0 - y, x0 + x, y0 - y, attr);
    	   drawLine(x0 - y, y0 - x, x0 + y, y0 - x, attr);
    	}
    	drawPixel(x0 - y, y0 + x, attr);
    	drawPixel(x0 + y, y0 + x, attr);
    	drawPixel(x0 - x, y0 + y, attr);
        drawPixel(x0 + x, y0 + y, attr);
    	drawPixel(x0 - x, y0 - y, attr);
    	drawPixel(x0 + x, y0 - y, attr);
    	drawPixel(x0 - y, y0 - x, attr);
    	drawPixel(x0 + y, y0 - x, attr);

    	if (err <= 0) {
    	    y += 1;
    	    err += (2 * y) + 1;
    	}

    	if (err > 0) {
    	    x -= 1;
    	    err -= (2 * x) + 1;
    	}
    }
}

void wait_msec(unsigned int n) {
    register unsigned long f, t, r;

    // Get the current counter frequency
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));
    // Read the current counter
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));
    // Calculate expire value for counter
    t += ((f / 1000) * n) / 1000;
    do {
        asm volatile ("mrs %0, cntpct_el0" : "=r" (r));
    } while(r < t);
}
