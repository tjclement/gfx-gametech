/* Computer Graphics, Assignment 1, Bresenham's Midpoint Line-Algorithm
 *
 * Filename ........ mla.c
 * Description ..... Midpoint Line Algorithm
 * Created by ...... Jurgen Sturm 
 *
 * Student name Tom Clement & Matthijs Klijn
 * Student email Tom.justme@gmail.com, matthijsthoolen@hotmail.com
 * Collegekaart 10468498, 10447822
 * Date 4-2-2016
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include "SDL.h"
#include "init.h"
#include "mla.h"

/*
 * Writes a pixel of the given colour to a position x,y after translating the origin system
 * and octant transformation of those coordinates.
 */
void WriteNormalizedPixel(SDL_Surface *s, int octant, int x, int y, Uint32 colour) {
    FromOctantZeroTo(octant, &x, &y);
    ToTopLeftOrigin(s, &x, &y);
    PutPixel(s, x, y, colour);
}

/*
 * Translates x and y values from a system that has the origin in the top left,
 * to one that has the origin in the middle of the screen.
 */
void ToCenterOrigin(SDL_Surface *s, int *x, int *y) {
    int mid_x = s->w / 2, mid_y = s->h / 2;
    *x -= mid_x;
    *y -= mid_y;
}

/*
 * Translates x and y values from a system that has the origin in the center,
 * to one that has the origin in the top left of the screen.
 */
void ToTopLeftOrigin(SDL_Surface *s, int *x, int *y) {
    int mid_x = s->w / 2, mid_y = s->h / 2;
    *x += mid_x;
    *y += mid_y;
}

/*
 * Translates x and y values from the source octant to octant 0.
 */
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

/*
 * Translates x and y values from octant 0 to the target octant.
 */
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

/*
 * Determines the octant a line is in based on its width and height.
 */
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
 * Draws a line on the screen based on Bresenham's Midpoint Line Algorithm
 */
void mla(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 colour) {
    int width = x1 - x0, height = y1 - y0;
    ToCenterOrigin(s, &x0, &y0);
    ToCenterOrigin(s, &x1, &y1);

    int octant = DetermineOctant(width, height);
    ToOctantZeroFrom(octant, &x0, &y0);
    ToOctantZeroFrom(octant, &x1, &y1);

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
