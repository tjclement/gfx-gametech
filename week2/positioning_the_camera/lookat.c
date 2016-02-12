/* Computer Graphics, Assignment 4, Positioning the camera
 *
 * Filename ........ lookat.c
 * Description ..... Contains the re-programmed lookAt function
 * Created by ...... Jurgen Sturm 
 *
 * Student name Tom Clement & Matthijs Klijn
 * Student email Tom.justme@gmail.com, matthijsthoolen@hotmail.com
 * Collegekaart 10468498, 10447822
 * Date 11-2-2016
 * Comments ........
 *
 */
#include <GL/glut.h>   
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>


/*
 * Compute the crossproduct from the two given vectors and stores them in
 * the result vector
 */
void crossProduct(GLdouble *A, GLdouble *B, GLdouble *result) {
    result[0] = A[1] * B[2] - A[2] * B[1];
    result[1] = A[2] * B[0] - A[0] * B[2];
    result[2] = A[0] * B[1] - A[1] * B[0];
}


/*
 * Normalize the given vector
 */
void normalize(GLdouble *A) {
    GLdouble length = sqrt(A[0] * A[0]
                           + A[1] * A[1]
                           + A[2] * A[2]);
    A[0] /= length;
    A[1] /= length;
    A[2] /= length;
}


/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

void myLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
              GLdouble centerX, GLdouble centerY, GLdouble centerZ,
              GLdouble upX, GLdouble upY, GLdouble upZ) {

    GLdouble center[3] = {centerX, centerY, centerZ};
    GLdouble eye[3] = {eyeX, eyeY, eyeZ};
    GLdouble up[3] = {upX, upY, upZ};

    GLdouble n[3], u[3], v[3];

    // compute n, n is the vector from the eye to the center
    n[0] = eye[0] - center[0];
    n[1] = eye[1] - center[1];
    n[2] = eye[2] - center[2];
    normalize(n);

    //compute u = up * n
    crossProduct(up, n, u);
    normalize(u);

    // compute v = n * u
    crossProduct(n, u, v);
    normalize(v);

    // Finally compute the rotation matrix
    GLfloat rotate[16] =
    {
            u[0], v[0], n[0], 0.0,
            u[1], v[1], n[1], 0.0,
            u[2], v[2], n[2], 0.0,
            0.0,  0.0,  0.0,  1.0
    };

    // Call opengl functions
    glMultMatrixf(rotate);
    glTranslatef(eyeX, eyeY, eyeZ);

}