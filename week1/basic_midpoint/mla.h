/* Computer Graphics, Assignment 1, Bresenham's Midpoint Line-Algorithm
 *
 * Filename ........ mla.h
 * Description ..... Header file for mla.c
 * Created by ...... Jurgen Sturm 
 *
 */

#ifndef JS_MLA_H
#define JS_MLA_H

void mla(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 colour);
void WriteNormalizedPixel(SDL_Surface *s, int octant, int x, int y, Uint32 colour);

void ToCenterOrigin(SDL_Surface *s, int *x, int *y);

void ToTopLeftOrigin(SDL_Surface *s, int *x, int *y);

void ToOctantZeroFrom(int octant, int *x, int *y);

void FromOctantZeroTo(int octant, int *x, int *y);

int DetermineOctant(int width, int height);
#endif /* JS_MLA_H */
