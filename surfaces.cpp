#include "splashkit.h"
#include "surfaces.h"

bitmap surface_bitmap(surface_kind kind)
{
    switch (kind)
    {
    case SURFACE1:
        return bitmap_named("surface1");
        break;
    case SURFACE2:
        return bitmap_named("surface2");
        break;
    case SURFACE3:
        return bitmap_named("surface3");
        break;
    case SURFACE4:
        return bitmap_named("surface4");
        break;
    default:
        return bitmap_named("surface1");
        break;
    }
}

surfaces new_surface(double &x, int level)
{
    surfaces result;
    if (level == 1)
    {
        result.kind = static_cast<surface_kind>(rnd(0, 1));
    }
    if (level == 2)
    {
        result.kind = static_cast<surface_kind>(rnd(2, 4));
    }
    result.surface_sprite = create_sprite(surface_bitmap(result.kind));
    sprite_set_collision_kind(result.surface_sprite, AABB_COLLISIONS);
    sprite_set_x(result.surface_sprite, x);
    sprite_set_scale(result.surface_sprite, 0.7);
    if (result.kind == SURFACE1 or result.kind == SURFACE3)
    {
        sprite_set_y(result.surface_sprite, camera_y() + rnd(200, 300));
        x = x + sprite_width(result.surface_sprite) + rnd(0, 1000);
    }
    if (result.kind == SURFACE2 or result.kind == SURFACE4)
    {
        sprite_set_y(result.surface_sprite, camera_y() + rnd(200, 300));
        x = x + sprite_width(result.surface_sprite) + rnd(0, 1000);
    }

    return result;
}

void update_surface(surfaces &surface_to_update)
{
    update_sprite(surface_to_update.surface_sprite);
}