#include "splashkit.h"
#include "powerup.h"

bitmap power_up_bitmap(power_up_kind kind)
{
    switch (kind)
    {
    case XP:
        return bitmap_named("xp");
        break;
    case SHIELD:
        return bitmap_named("shield");
        break;
    case LIFE:
        return bitmap_named("life");
        break;
    case TIME:
        return bitmap_named("time");
        break;
    default:
        return bitmap_named("xp");
        break;
    }
}

power_up_data new_power_up(double &x)
{
    power_up_data result;
    result.kind = static_cast<power_up_kind>(rnd(4));
    result.power_up_sprite = create_sprite(power_up_bitmap(result.kind));
    sprite_set_x(result.power_up_sprite, x + rnd(-400, 400));
    x = x + sprite_width(result.power_up_sprite) + rnd(0, 1000);
    sprite_set_y(result.power_up_sprite, rnd(200, 300));
    sprite_set_scale(result.power_up_sprite, 0.6);
    return result;
}

void update_power_up(power_up_data &power_up_to_update)
{
    update_sprite(power_up_to_update.power_up_sprite);
}