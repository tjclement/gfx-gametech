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

    int hasBegunRow;

    float x_min = findlow(x0, x1, x2);
    float x_max = findhigh(x0, x1, x2);

    float y_min = findlow(y0, y1, y2);
    float y_max = findhigh(y0, y1, y2);

    const float f_alpha = f(x1, y1, x2, y2, x0, y0);
    const float f_beta = f(x2, y2, x0, y0, x1, y1);
    const float f_gamma = f(x0, y0, x1, y1, x2, y2);

    const float f_out_alpha = f(x1, y1, x2, y2, -1, -1) * f_alpha;
    const float f_out_beta = f(x2, y2, x0, y0, -1, -1) * f_beta;
    const float f_out_gamma = f(x0, y0, x1, y1, -1, -1) * f_gamma;

    float f_alpha_increment_x = (y1 - y2);
    float f_alpha_increment_y = (x2 - x1);
    float f_beta_increment_x = (y2 - y0);
    float f_beta_increment_y = (x0 - x2);
    float f_gamma_increment_x = (y0 - y1);
    float f_gamma_increment_y = (x1 - x0);

    float x, y, alpha_incremental, beta_incremental, gamma_incremental;
    float alpha_orig = f(x1, y1, x2, y2, x_min, y_min) / f_alpha;
    float beta_orig = f(x2, y2, x0, y0, x_min, y_min) / f_beta;
    float gamma_orig = f(x0, y0, x1, y1, x_min, y_min) / f_gamma;

    // For each pixel in the triangle check if we need to print it
    for (y = y_min; y < y_max; y++) {
        hasBegunRow = 0;
        alpha_incremental = alpha_orig;
        beta_incremental = beta_orig;
        gamma_incremental = gamma_orig;
        
        for (x = x_min; x < x_max; x++) {
            if (alpha_incremental >= 0.0 && beta_incremental >= 0.0 && gamma_incremental >= 0.0) {
                if ((f(x1, y1, x2, y2, x, y) / f_alpha > 0.0 || f_out_alpha > 0.0)
                    && (f(x2, y2, x0, y0, x, y) / f_beta > 0.0 || f_out_beta > 0.0)
                    && (f(x0, y0, x1, y1, x, y) / f_gamma > 0.0 || f_out_gamma > 0.0)) {
                    PutPixel(x, y, r, g, b);
                    hasBegunRow = 1;
                }
            } else if(hasBegunRow) {
                break;
            }
            alpha_incremental += f_alpha_increment_x;
            beta_incremental += f_beta_increment_x;
            gamma_incremental += f_gamma_increment_x;
        }

        alpha_orig += f_alpha_increment_y;
        beta_orig += f_beta_increment_y;
        gamma_orig += f_gamma_increment_y;
    }

}