/*
 * hello.c
 * this program is a simple GBA example
 * it simply creates a colored screen and waits
 */

#include <stdlib.h>

/* the width and height of the screen */
#define WIDTH 240
#define HEIGHT 160

/* these identifiers define different bit positions of the display control */
#define MODE3 0x0003
#define BG2 0x0400

/* the screen is simply a pointer into memory at a specific address this
 * pointer points to 16-bit colors of which there are 240x160 */
volatile unsigned short* screen = (volatile unsigned short*) 0x6000000;

volatile unsigned short* buttonInput = (volatile unsigned short*) 0x4000130;

/* the display control pointer points to the gba graphics register */
volatile unsigned long* display_control = (volatile unsigned long*) 0x4000000;

/* compute a 16-bit integer color based on the three components */
unsigned short make_color(unsigned char r, unsigned char g, unsigned char b) {
    unsigned short color = (b & 0x1f) << 10;
    color |= (g & 0x1f) << 5;
    color |= (r & 0x1f);
    return color;
}

/* place a pixel of a given color on the screen */
void put_pixel(int row, int col, unsigned short color) {
    /* set the screen location to this color */
    screen[row * WIDTH + col] = color;
}

unsigned short randomColor()
{
    return unsigned short color = rand() >> 16;
}

void buttonPress()
{
    if ((!buttonInput &= 0x1) ||
        (!buttonInput &= 0x2) ||
        (!buttonInput &= 0x4) ||
        (!buttonInput &= 0x8) ||
        (!buttonInput &= 0x10) ||
        (!buttonInput &= 0x20) ||
        (!buttonInput &= 0x40) ||
        (!buttonInput &= 0x80) ||
        (!buttonInput &= 0x100) ||
        (!buttonInput &= 0x200) ||)
    {
        for (int row = 0; row < HEIGHT; row++) 
        { 
            for (int col = 0; col < WIDTH; col++) 
            {
                put_pixel(row, col, randomColor());
            }
        }
    }
}

int main() { 
    /* we set the mode to mode 3 with background 2 on */
    *display_control = MODE3 | BG2;

    /* loop through each row of the screen */
    for (int row = 0; row < HEIGHT; row++) { 

        /* make a color in the range of black to bright blue based on the row */
        unsigned short color = make_color(0, 0, row % 32);

        /* loop through each column of the screen */
        for (int col = 0; col < WIDTH; col++) {
            put_pixel(row, col, color);
        }
    }

    /* we now loop forever displaying the image */
    while (1) {
        buttonPress();
    }
}

/* the game boy advance uses "interrupts" to handle certain situations
 * for now we will ignore these */
void interrupt_ignore() {
    /* do nothing */
}

/* this table specifies which interrupts we handle which way
 * for now, we ignore all of them */
typedef void (*intrp)();
const intrp IntrTable[13] = {
    interrupt_ignore,   /* V Blank interrupt */
    interrupt_ignore,   /* H Blank interrupt */
    interrupt_ignore,   /* V Counter interrupt */
    interrupt_ignore,   /* Timer 0 interrupt */
    interrupt_ignore,   /* Timer 1 interrupt */
    interrupt_ignore,   /* Timer 2 interrupt */
    interrupt_ignore,   /* Timer 3 interrupt */
    interrupt_ignore,   /* Serial communication interrupt */
    interrupt_ignore,   /* DMA 0 interrupt */
    interrupt_ignore,   /* DMA 1 interrupt */
    interrupt_ignore,   /* DMA 2 interrupt */
    interrupt_ignore,   /* DMA 3 interrupt */
    interrupt_ignore,   /* Key interrupt */
};