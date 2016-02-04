/* Computer Graphics assignment, Triangle Rasterization
 * Filename ........ trirast.c
 * Description ..... Implements triangle rasterization
 * Created by ...... Paul Melis
 *
 * Student name Tom Clement & Matthijs Klijn
 * Student email Tom.justme@gmail.com, matthijsthoolen@hotmail.com
 * Collegekaart ????????, 10447822
 * Date 4-2-2016
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "types.h"

/*
 * Rasterize a single triangle.
 * The triangle is specified by its corner coordinates
 * (x0,y0), (x1,y1) and (x2,y2).
 * The triangle is drawn in color (r,g,b).
 */


/*
 * Returns the lowest of 3 floats
 */
float findlow(float x0, float x1, float x2) {

    if (x1 < x0) x0 = x1;

    if (x2 < x0) x0 = x2;

    return x0;
}


/*
 * Returns the highest of 3 floats
 */
float findhigh(float x0, float x1, float x2) {

    if (x1 > x0) x0 = x1;

    if (x2 > x0) x0 = x2;

    return x0;
}


/*
 * Returns value for line through (x0, y0) and (x1, y1) using (px, py)
 */
float lineval(float x0, float y0, float x1, float y1,
              float px, float py) {

    return (y0 - y1) * px + (x1 - x0) * py + x0 * y1 - x1 * y0;
}


void draw_triangle(float x0, float y0, float x1, float y1, float x2, float y2,
                   byte r, byte g, byte b) {

    float x_min = findlow(x0, x1, x2);
    float x_max = findhigh(x0, x1, x2);

    float y_min = findlow(y0, y1, y2);
    float y_max = findhigh(y0, y1, y2);

    // For each pixel in the triangle check if we need to print it
    for (float y = y_min; y < y_max; ++y) {
        for (float x = x_min; x < x_max; ++x) {

            float alpha = lineval(x1, y1, x2, y2, x, y) / lineval(x1, y1, x2, y2, x0, y0);
            float beta = lineval(x2, y2, x0, y0, x, y) / lineval(x2, y2, x0, y0, x1, y1);
            float gamma = lineval(x0, y0, x1, y1, x, y) / lineval(x0, y0, x1, y1, x2, y2);

            if (alpha >= 0.0 && beta >= 0.0 && gamma >= 0.0) {

                if ((alpha > 0.0 || lineval(x1, y1, x2, y2, -1, -1) * lineval(x1, y1, x2, y2, x0, y0) > 0.0)
                    && (beta > 0.0 || lineval(x2, y2, x0, y0, -1, -1) * lineval(x2, y2, x0, y0, x1, y1) > 0.0)
                    && (gamma > 0.0 || lineval(x0, y0, x1, y1, -1, -1) * lineval(x0, y0, x1, y1, x2, y2) > 0.0)) {
                    PutPixel(x, y, r, g, b);
                }

            }

        }
    }
}


void draw_triangle_optimized(float x0, float y0, float x1, float y1, float x2, float y2,
                             byte r, byte g, byte b) {

    float alpha, beta, gamma;

    float x_min = findlow(x0, x1, x2);
    float x_max = findhigh(x0, x1, x2);

    float y_min = findlow(y0, y1, y2);
    float y_max = findhigh(y0, y1, y2);

    // For each pixel in the triangle check if we need to print it
    for (float y = y_min; y < y_max; ++y) {
        for (float x = x_min; x < x_max; ++x) {

            alpha = lineval(x1, y1, x2, y2, x, y) / lineval(x1, y1, x2, y2, x0, y0);
            beta = lineval(x2, y2, x0, y0, x, y) / lineval(x2, y2, x0, y0, x1, y1);
            gamma = lineval(x0, y0, x1, y1, x, y) / lineval(x0, y0, x1, y1, x2, y2);

            if (alpha >= 0.0 && beta >= 0.0 && gamma >= 0.0) {

                if ((alpha > 0.0 || lineval(x1, y1, x2, y2, -1, -1) * lineval(x1, y1, x2, y2, x0, y0) > 0.0)
                    && (beta > 0.0 || lineval(x2, y2, x0, y0, -1, -1) * lineval(x2, y2, x0, y0, x1, y1) > 0.0)
                    && (gamma > 0.0 || lineval(x0, y0, x1, y1, -1, -1) * lineval(x0, y0, x1, y1, x2, y2) > 0.0)) {
                    PutPixel(x, y, r, g, b);
                }

            }

        }
    }

}