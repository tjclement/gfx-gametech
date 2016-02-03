/* Computer Graphics, Assignment 1, Bresenham's Midpoint Line-Algorithm
 *
 * Filename ........ mla.c
 * Description ..... Midpoint Line Algorithm
 * Created by ...... Jurgen Sturm 
 *
 * Student name ....
 * Student email ... 
 * Collegekaart ....
 * Date ............
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include "SDL.h"
#include "init.h"

void WriteNormalizedPixel(SDL_Surface *s, int octant, int x, int y, Uint32 colour) {
    int mid_x=s->w/2, mid_y=s->h/2;


    switch(octant) {
        case 0:
            PutPixel(s, x, y, colour);
            break;
        case 1:
            PutPixel(s, y, x, colour);
            break;
        case 2:
            PutPixel(s, mid_x-(mid_x-y), x, colour);
            break;
        case 3:
            PutPixel(s, mid_x-(mid_x-x), y, colour);
            break;
        case 4:
            PutPixel(s, mid_x-(mid_x-x), mid_y-(mid_y-y), colour);
            break;
        case 5:
            PutPixel(s, mid_x-(mid_x-y), mid_y-(mid_y-x), colour);
            break;
        case 6:
            PutPixel(s, y, mid_y-(mid_y-x), colour);
            break;
        case 7:
            PutPixel(s, x, mid_y-(mid_y-y), colour);
            break;
    }
}

/*
 * Midpoint Line Algorithm
 *
 * As you probably will have figured out, this is the part where you prove
 * your programming skills. The code in the mla function should draw a direct 
 * line between (x0,y0) and (x1,y1) in the specified color. 
 * 
 * Until now, the example code below draws only a horizontal line between
 * (x0,y0) and (x1,y0) and a vertical line between (x1,y1).
 * 
 * And here the challenge begins..
 *
 * Good luck!
 *
 *
 */
void mla(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 colour) {
    int x = x0, y = y0, width = x1 - x0, height = y1 - y0;

    int octant;

    if(width > 0 && height <= 0) {
        octant = width >= height ? 0 : 1;
    } else if(width <= 0 && height <= 0) {
        octant = abs(width) < abs(height) ? 2 : 3;
    } else if(width < 0 && height >= 0) {
        octant = abs(width) > height ? 4 : 5;
    } else if (width >= 0 && height > 0) {
        octant = width < height ? 6 : 7;
    }

    /* https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Line_equation */

    height = abs(height);
    width = abs(width);

    int d = 2 * height - width;
    printf("%d %d", x, y);
    WriteNormalizedPixel(s, octant, x, y, colour);
    if (d > 0) {
        y -= 1;
        d -= 2 * width;
    }

    for (; (x1 < 0 && x > x1) || x < x1; x += 1) {
        WriteNormalizedPixel(s, octant, x, y, colour);
        d += 2 * height;
        if (d > 0) {
            y -= 1;
            d -= 2 * width;
        }
    }

    return;
}
