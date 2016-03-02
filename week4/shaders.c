/* Computer Graphics and Game Technology, Assignment Ray-tracing
 *
 * Student name Tom Clement & Matthijs Klijn
 * Student email Tom.justme@gmail.com, matthijsthoolen@hotmail.com
 * Collegekaart 10468498, 10447822
 * Date 1-3-2016
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "shaders.h"
#include "perlin.h"
#include "v3math.h"
#include "intersection.h"
#include "scene.h"
#include "quat.h"
#include "constants.h"

// shade_constant()
//
// Always return the same color. This shader does no real computations
// based on normal, light position, etc. As such, it merely creates
// a "silhouette" of an object.

vec3
shade_constant(intersection_point ip)
{
    return v3_create(1, 0, 0);
}

vec3
shade_matte(intersection_point ip)
{
    float lightContribution = 0;
    for(int i = 0; i < scene_num_lights; i++) {
        vec3 li = v3_normalize(v3_subtract(scene_lights[i].position, ip.p));
        
        lightContribution += scene_lights[i].intensity * fmaxf(0.0, v3_dotprod(ip.n, li));
    }
    lightContribution += scene_ambient_light;
    return v3_create(lightContribution, lightContribution, lightContribution);
}

vec3
shade_blinn_phong(intersection_point ip)
{

    vec3 li, h;
    float matte = 0, phong = 0;

    // Loop through all the light points
    for(int i = 0; i < scene_num_lights; i++)
    {
        // Vector for the light
        li = v3_normalize(v3_subtract(scene_lights[i].position, ip.p));

        h = v3_normalize(v3_add(ip.i, li));

        // Add the highlight to phong
        phong += (scene_lights[i].intensity * fmaxf(0, pow(v3_dotprod(h, ip.n), 50)));

        if(!shadow_check(v3_add(ip.p, v3_multiply(ip.n, 0.0005)), scene_lights[i].position))
        {
            // If there is no shadow, calculate the scene light color/intensity
            matte += (scene_lights[i].intensity * fmaxf(0, v3_dotprod(ip.n, li)));
        }

    }

    // Multiply with kd and add the ambient lightning
    matte *= 0.8 + scene_ambient_light;

    // Multiply phong with ks
    phong *= 0.5;

    vec3 cd = v3_multiply(v3_create(1, 0, 0), matte);
    vec3 cs = v3_multiply(v3_create(1, 1, 1), phong);

    return v3_add(cd, cs);
}

vec3
shade_reflection(intersection_point ip)
{
    return v3_create(1, 0, 0);
}

// Returns the shaded color for the given point to shade.
// Calls the relevant shading function based on the material index.
vec3
shade(intersection_point ip)
{
  fprintf(stderr, "%d", ip.material);
  switch (ip.material)
  {
    case 0:
      return shade_constant(ip);
    case 1:
      return shade_matte(ip);
    case 2:
      return shade_blinn_phong(ip);
    case 3:
      return shade_reflection(ip);
    default:
      return shade_constant(ip);

  }
}

// Determine the surface color for the first object intersected by
// the given ray, or return the scene background color when no
// intersection is found
vec3
ray_color(int level, vec3 ray_origin, vec3 ray_direction)
{
    intersection_point  ip;

    // If this ray has been reflected too many times, simply
    // return the background color.
    if (level >= 3)
        return scene_background_color;

    // Check if the ray intersects anything in the scene
    if (find_first_intersection(&ip, ray_origin, ray_direction))
    {
        // Shade the found intersection point
        ip.ray_level = level;
        return shade(ip);
    }

    // Nothing was hit, return background color
    return scene_background_color;
}
