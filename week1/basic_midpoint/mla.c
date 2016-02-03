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
#include "mla.h"

void WriteNormalizedPixel(SDL_Surface *s, int octant, int x, int y, Uint32 colour) {
    FromOctantZeroTo(octant, &x, &y);
    ToTopLeftOrigin(s, &x, &y);
    if(x<0 || y<0){
        printf(" x.x %d %d\r\n", x, y);
        return;
    }
    PutPixel(s, x, y, colour);
}

void ToCenterOrigin(SDL_Surface *s, int *x, int *y) {
    int mid_x = s->w / 2, mid_y = s->h / 2;
    *x -= mid_x;
    *y -= mid_y;
}

void ToTopLeftOrigin(SDL_Surface *s, int *x, int *y) {
    int mid_x = s->w / 2, mid_y = s->h / 2;
    *x += mid_x;
    *y += mid_y;
}

void ToOctantZeroFrom(int octant, int *x, int *y) {
    if (octant == 1 || octant == 2 || octant == 5 || octant == 6) {
        /* Flip x and y axes */
        int tmp = *x;
        *x = *y;
        *y = tmp;
    }

    if (octant == 1 || octant == 2 || octant == 3 || octant == 4) {
        /* Negate first axis*/
        *x *= -1;
    }

    if (octant == 1 || octant == 4 || octant == 6 || octant == 7) {
        /* Negate second axis*/
        *y *= -1;
    }
}

void FromOctantZeroTo(int octant, int *x, int *y) {
    if (octant == 1 || octant == 2 || octant == 5 || octant == 6) {
        /* Flip x and y axes */
        int tmp = *x;
        *x = *y;
        *y = tmp;
    }

    if (octant == 1 || octant == 3 || octant == 4 || octant == 6) {
        /* Negate first axis*/
        *x *= -1;
    }

    if (octant == 1 || octant == 2 || octant == 4 || octant == 7) {
        /* Negate second axis*/
        *y *= -1;
    }
}

int DetermineOctant(int width, int height) {
    if (width > 0 && height <= 0) {
        return width >= abs(height) ? 0 : 1;
    } else if (width <= 0 && height <= 0) {
        return abs(width) < abs(height) ? 2 : 3;
    } else if (width < 0 && height >= 0) {
        return abs(width) > height ? 4 : 5;
    } else if (width >= 0 && height > 0) {
        return width < height ? 6 : 7;
    }
    printf("Serious error: no such octant exists.");
    exit(-1);
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
    printf("1 - %d %d %d %d\r\n", x0, y0, x1, y1);
    int width = x1 - x0, height = y1 - y0;
    ToCenterOrigin(s, &x0, &y0);
    ToCenterOrigin(s, &x1, &y1);

    printf("2 - %d %d %d %d\r\n", x0, y0, x1, y1);
    int octant = DetermineOctant(width, height);
    ToOctantZeroFrom(octant, &x0, &y0);
    ToOctantZeroFrom(octant, &x1, &y1);
    printf("3 - %d %d %d %d\r\n", x0, y0, x1, y1);

    /* Width/height need to be calculated again after potentially swapping axes */
    width = abs(x1 - x0), height = abs(y1 - y0);

    /* https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Line_equation */

    int d = 2 * height - width;
    WriteNormalizedPixel(s, octant, x0, y0, colour);
    if (d > 0) {
        y0 -= 1;
        d -= 2 * width;
    }

    for (; (x1 < 0 && x0 > x1) || x0 < x1; x0 += 1) {
        WriteNormalizedPixel(s, octant, x0, y0, colour);
        d += 2 * height;
        if (d > 0) {
            y0 -= 1;
            d -= 2 * width;
        }
    }

    return;
}
