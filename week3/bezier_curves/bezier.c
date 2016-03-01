/* Computer Graphics, Assignment, Bezier curves
 * Filename ........ bezier.c
 * Description ..... Bezier curves
 * Date ............ 22.07.2009
 * Created by ...... Paul Melis
 *
 * Student name Tom Clement & Matthijs Klijn
 * Student email Tom.justme@gmail.com, matthijsthoolen@hotmail.com
 * Collegekaart 10468498, 10447822
 * Date 18-2-2016
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <math.h>
#include "bezier.h"
#include <stdio.h>

/*
 * Calculate the factorial of a given ingeger n
 */
long factorial(int n) {
    long result = 1;

    for (int c = 1; c <= n; c++) {
        result = result * c;
    }

    return result;
}

/*
 * Calculate the binomial distribution of the given n and k
 */
double binomial_distribution(int n, int k) {
    return factorial(n) / (double) (factorial(k) * factorial(n - k));
}

/*
 * Calculate the bernstein polynomial with given n, i and u
 */
double bernstein_polynomial(int n, int i, float u) {
    return binomial_distribution(n, i) * pow(u, (double) i) * pow((1 - u), (double) (n - i));
}

/* Given a Bezier curve defined by the 'num_points' control points
 * in 'p' compute the position of the point on the curve for parameter
 * value 'u'.
 *
 * Return the x and y values of the point by setting *x and *y,
 * respectively.
 */

void evaluate_bezier_curve(float *x, float *y, control_point p[], int num_points, float u) {
    *x = 0.0;
    *y = 0.0;
    double bernstein = 0.0;

    // Calculate the x and y coordinates for every control point
    for (int i = 0; i < num_points; i++) {
        bernstein = bernstein_polynomial(num_points - 1, i, u);
        *x += bernstein * p[i].x;
        *y += bernstein * p[i].y;
    }
}

/* Draw a Bezier curve defined by the control points in p[], which
 * will contain 'num_points' points.
 *
 * Draw the line segments you compute directly on the screen
 * as a single GL_LINE_STRIP. This is as simple as using
 *
 *      glBegin(GL_LINE_STRIP);
 *      glVertex2f(..., ...);
 *      ...
 *      glEnd();
 *
 * DO NOT SET ANY COLOR!
 *
 * The 'num_segments' parameter determines the "discretization" of the Bezier
 * curve and is the number of straight line segments that should be used
 * to approximate the curve.
 *
 * Call evaluate_bezier_curve() to compute the necessary points on
 * the curve.
 */

void draw_bezier_curve(int num_segments, control_point p[], int num_points) {
    float x, y;

    glBegin(GL_LINE_STRIP);

    // Approximate the x and y coordinaties with evaluate_bezier_curve for 0 to 1, to 1.001 to prevent
    // flaot precision errors
    for (double u = 0; u <= 1.001; u += 0.001) {
        evaluate_bezier_curve(&x, &y, p, num_points, u);
        glVertex2f(x, y);
    }
    glEnd();
}

/* Find the intersection of a cubic Bezier curve with the line X=x.
 * Return 1 if an intersection was found and place the corresponding y
 * value in *y.
 * Return 0 if no intersection exists.
 */

int intersect_cubic_bezier_curve(float *y, control_point p[], float x) {
    float bezier_x, bezier_y;

    // Find if the point is intersected for every point between 0 and 1.001
    for (double u = 0; u <= 1.001; u += 0.001) {
        evaluate_bezier_curve(&bezier_x, &bezier_y, p, 4, u);

        // If there is an intersection return true and set the Y value
        if (fabs(bezier_x - x) <= 0.001) {
            *y = bezier_y;
            return 1;
        }
    }

    return 0;
}

