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
//    PutPixel(s, x1, y1, colour);
    int x = x0, y = y0, width = x1 - x0, height = y1 - y0;
    int dx, dy;

    /* https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Line_equation */

    if (x1 - x0 > 0) {
        /* Righthand quadrants */
        dx = 1;
    } else {
        /* Lefthand quadrants */
        dx = -1;
    }

    if (y1 - y0 < 0) {
        /* Top quadrants */
        dy = 1;
    } else {
        /* Bottom quadrants */
        dy = -1;
    }

    int d = 2*height - width;
    PutPixel(s, x, y, colour);
    if (d > 0) {
        y += dy;
        d -= 2*width;
    }

    for (; (x1 < 0 && x > x1) || x < x1; x += dx) {
        PutPixel(s, x, y, colour);
        d += 2*height;
        if (d > 0) {
            y += dy;
            d -= 2*width;
        }
    }

    return;
}
