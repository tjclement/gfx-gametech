/* Computer Graphics, Assignment, Volume rendering with cubes/points/isosurface
 *
 * Student name Tom Clement & Matthijs Klijn
 * Student email Tom.justme@gmail.com, matthijsthoolen@hotmail.com
 * Collegekaart 10468498, 10447822
 * Date 11-3-2016
 * Comments ........
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "marching_tetrahedra.h"

/* Compute a linearly interpolated position where an isosurface cuts
   an edge between two vertices (p1 and p2), each with their own
   scalar value (v1 and v2) */

static vec3
interpolate_points(unsigned char isovalue, vec3 p1, vec3 p2, unsigned char v1, unsigned char v2)
{
    /* Initially, simply return the midpoint between p1 and p2.
       So no real interpolation is done yet */
    
    float ratio1 = v1 < v2 ? (isovalue - v1) / (v2 - v1) : 1 - ((isovalue - v2) / (v1 - v2));
    float ratio2 = 1 - ratio1;
    

    return v3_add(v3_multiply(p1, ratio1), v3_multiply(p2, ratio2));
}

int generate_triangle(triangle *triangles, unsigned char isovalue, cell c, int v0, int v1, int v2, int v3, int v4, int v5)
{
    /* Create triangle vertices */
    triangles->p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
    triangles->p[1] = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v3]);
    triangles->p[2] = interpolate_points(isovalue, c.p[v4], c.p[v5], c.value[v4], c.value[v5]);
    
    vec3 normal = v3_normalize(v3_crossprod(v3_subtract(c.p[v1], c.p[v0]), v3_subtract(c.p[v3], c.p[v2])));
    
    triangles->n[0] = normal;
    triangles->n[1] = normal;
    triangles->n[2] = normal;
    
    return 1;
}

/* Using the given iso-value generate triangles for the tetrahedron
   defined by corner vertices v0, v1, v2, v3 of cell c.

   Store the resulting triangles in the "triangles" array.

   Return the number of triangles created (either 0, 1, or 2).

   Note: the output array "triangles" should have space for at least
         2 triangles.
*/

static int
generate_tetrahedron_triangles(triangle *triangles, unsigned char isovalue, cell c, int v0, int v1, int v2, int v3)
{
    int bit_value = 0x00;
    
    bit_value += c.value[v0] > isovalue ? 1 : 0;
    bit_value += c.value[v1] > isovalue ? 2 : 0;
    bit_value += c.value[v2] > isovalue ? 4 : 0;
    bit_value += c.value[v3] > isovalue ? 8 : 0;
    
    switch(bit_value) {
        case 0x00:
            return 0;
        case 0x01:
        case 0x0E:
            return generate_triangle(triangles, isovalue, c, v0, v1, v0, v2, v0, v3);
        case 0x02:
        case 0x0D:
            return generate_triangle(triangles, isovalue, c, v1, v2, v1, v3, v1, v0);
        case 0x04:
        case 0x0B:
            return generate_triangle(triangles, isovalue, c, v2, v1, v2, v3, v2, v0);
        case 0x08:
        case 0x07:
            return generate_triangle(triangles, isovalue, c, v3, v0, v3, v1, v3, v2);
        case 0x03:
        case 0x0C:
            return generate_triangle(triangles, isovalue, c, v1, v3, v1, v2, v3, v0) +
                   generate_triangle(triangles, isovalue, c, v3, v0, v0, v2, v2, v1);
        case 0x05:
        case 0x0A:
            return generate_triangle(triangles, isovalue, c, v0, v3, v3, v2, v2, v1) +
                   generate_triangle(triangles, isovalue, c, v0, v3, v0, v1, v1, v2);
        case 0x06:
        case 0x09:
            return generate_triangle(triangles, isovalue, c, v3, v2, v2, v0, v3, v1) +
                   generate_triangle(triangles, isovalue, c, v0, v1, v0, v2, v3, v1);
        default:
            return 0;
            
    }
    
    
    return 0;
}

/* Generate triangles for a single cell for the given iso-value. This function
   should produce at most 6 * 2 triangles (for which the "triangles" array should
   have enough space).

   Use calls to generate_tetrahedron_triangles().

   Return the number of triangles produced
*/

int
generate_cell_triangles(triangle *triangles, cell c, unsigned char isovalue)
{
    int count = 0;
    count += generate_tetrahedron_triangles(&triangles[count], isovalue, c, 0, 1, 3, 7);
    count += generate_tetrahedron_triangles(&triangles[count], isovalue, c, 0, 1, 5, 7);
    count += generate_tetrahedron_triangles(&triangles[count], isovalue, c, 0, 2, 3, 7);
    count += generate_tetrahedron_triangles(&triangles[count], isovalue, c, 0, 2, 6, 7);
    count += generate_tetrahedron_triangles(&triangles[count], isovalue, c, 0, 4, 5, 7);
    count += generate_tetrahedron_triangles(&triangles[count], isovalue, c, 0, 4, 6, 7);
    
    return count;
}
