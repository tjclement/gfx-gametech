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
    int x = x0, y = y0, a = (y0 - y1), b = (x1 - x0), c = ((x0 * y1) - (x1 * y0));

    /* https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Line_equation
     * f(x, y) = ax + by + c = 0 */

    float slope = (float) (y1 - y0) / (x1 - x0);
    printf("%.2f %d\r\n", slope, colour);
    if (slope >= 0.0 && slope <= 1.0) {
        for (; x < x1; x += 1) {
            /* If f(x+1, y+0.5) >= 0, we need to decrement y */
            if(((a * (x + 1)) + (b * (y + 0.5)) + c) >= 0) {
                y++;
            }
            PutPixel(s, x, y, colour);
        }
    }

    return;
}
