#ifndef SURFACE
#define SURFACE

#include "splashkit.h"

// three kind of surfaces in the game
enum surface_kind
{
    SURFACE1,
    SURFACE2,
    SURFACE3,
    SURFACE4
};

// entity - surface, it has a sprite and a kind
struct surfaces
{
    sprite surface_sprite;
    surface_kind kind;
};

// this function returns the bitmap related to the surface in action
bitmap surface_bitmap(surface_kind kind);

// this function returns a random surface based on the surface kind and locate it on a random position on the x axis
surfaces new_surface(double &x, int level);


// this procedure update the surface related data dynamically as the player progresses
void update_surface(surfaces &surface_to_update);
#endif
