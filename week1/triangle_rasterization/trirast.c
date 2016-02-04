/* Computer Graphics assignment, Triangle Rasterization
 * Filename ........ trirast.c
 * Description ..... Implements triangle rasterization
 * Created by ...... Paul Melis
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
float findlow(float x, float y, float z) {
    if (y < x) x = y;
    if (z < x) x = z;
    return x;
}


/*
 * Returns the highest of 3 floats
 */
float findhigh(float x, float y, float z) {
    if (y > x) x = y;
    if (z > x) x = z;
    return x;
}


/*
 * Returns value for line through (x0, y0) and (x1, y1) using (px, py)
 */
float f(float x0, float y0, float x1, float y1,
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
    for (float y = y_min; y < y_max; y++) {
        for (float x = x_min; x < x_max; x++) {

            float alpha = f(x1, y1, x2, y2, x, y) / f(x1, y1, x2, y2, x0, y0);
            float beta = f(x2, y2, x0, y0, x, y) / f(x2, y2, x0, y0, x1, y1);
            float gamma = f(x0, y0, x1, y1, x, y) / f(x0, y0, x1, y1, x2, y2);

            if (alpha >= 0.0 && beta >= 0.0 && gamma >= 0.0) {

                if ((alpha > 0.0 || f(x1, y1, x2, y2, -1, -1) * f(x1, y1, x2, y2, x0, y0) > 0.0)
                    && (beta > 0.0 || f(x2, y2, x0, y0, -1, -1) * f(x2, y2, x0, y0, x1, y1) > 0.0)
                    && (gamma > 0.0 || f(x0, y0, x1, y1, -1, -1) * f(x0, y0, x1, y1, x2, y2) > 0.0)) {
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

    float f_alpha = f(x1, y1, x2, y2, x0, y0);
    float f_beta = f(x2, y2, x0, y0, x1, y1);
    float f_gamma = f(x0, y0, x1, y1, x2, y2);

    float f_out_alpha = f(x1, y1, x2, y2, -1, -1) * f_alpha;
    float f_out_beta = f(x2, y2, x0, y0, -1, -1) * f_beta;
    float f_out_gamma = f(x0, y0, x1, y1, -1, -1) * f_gamma;

    // For each pixel in the triangle check if we need to print it
    for (float y = y_min; y < y_max; y++) {
        for (float x = x_min; x < x_max; x++) {

            alpha = f(x1, y1, x2, y2, x, y) / f_alpha;
            beta = f(x2, y2, x0, y0, x, y) / f_beta;
            gamma = f(x0, y0, x1, y1, x, y) / f_gamma;

            if (alpha >= 0.0 && beta >= 0.0 && gamma >= 0.0) {

                if ((f(x1, y1, x2, y2, x, y) / f_alpha > 0.0 || f_out_alpha > 0.0)
                    && (f(x2, y2, x0, y0, x, y) / f_beta > 0.0 || f_out_beta > 0.0)
                    && (f(x0, y0, x1, y1, x, y) / f_gamma > 0.0 || f_out_gamma > 0.0)) {
                    PutPixel(x, y, r, g, b);
                }

            }

        }
    }

}