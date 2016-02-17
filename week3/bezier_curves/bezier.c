/* Computer Graphics, Assignment, Bezier curves
 * Filename ........ bezier.c
 * Description ..... Bezier curves
 * Date ............ 22.07.2009
 * Created by ...... Paul Melis
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

#include <math.h>
#include "bezier.h"
#include <stdio.h>

long factorial(int n) {
    long result = 1;

    for (int c = 1; c <= n; c++) {
        result = result * c;
    }

    return result;
}

double binomial_distribution(int n, int k) {
    return factorial(n) / (double)(factorial(k) * factorial(n - k));
}

double bernstein_polynomial(int n, int i, float u) {
    return binomial_distribution(n, i) * pow(u, (double)i) * pow((1 - u), (double)(n-i));
}

/* Given a Bezier curve defined by the 'num_points' control points
 * in 'p' compute the position of the point on the curve for parameter
 * value 'u'.
 *
 * Return the x and y values of the point by setting *x and *y,
 * respectively.
 */

void
evaluate_bezier_curve(float *x, float *y, control_point p[], int num_points, float u) {
    *x = 0.0;
    *y = 0.0;
    double bernstein = 0.0;

    for(int i = 0; i < num_points; i++) {
        bernstein = bernstein_polynomial(num_points-1, i, u);
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

void
draw_bezier_curve(int num_segments, control_point p[], int num_points) {
    float x, y;
    double stepSize = 1.0 / num_points;

    glBegin(GL_LINE_STRIP);
    for(double u = 0; u <= 1.001; u += 0.05) {
        evaluate_bezier_curve(&x, &y, p, num_points, u);
        glVertex2f(x, y);
    }
    glEnd();
}

/* Find the intersection of a cubic Bezier curve with the line X=x.
   Return 1 if an intersection was found and place the corresponding y
   value in *y.
   Return 0 if no intersection exists.
*/

int
intersect_cubic_bezier_curve(float *y, control_point p[], float x) {
    return 0;
}

