#include "splashkit.h"
#include "enemy.h"

bitmap enemy_bitmap(enemy_kind kind)
{
    switch (kind)
    {
    case MONSTER1:
        return bitmap_named("monster1");
        break;
    default:
        return bitmap_named("monster1");
        break;
    }
}

enemy new_enemy(double &x)
{
    enemy result;
    result.kind = static_cast<enemy_kind>(rnd(2));
    result.enemy_sprite = create_sprite(enemy_bitmap(result.kind), animation_script_named("mon"));
    sprite_start_animation(result.enemy_sprite, "walk");

    sprite_set_x(result.enemy_sprite, x + 300);
    x = x + sprite_width(result.enemy_sprite) + rnd(0, 1000);
    result.kill = 100;
    sprite_set_y(result.enemy_sprite, 170);
    result.velocity.x = rnd(-6, 6);
    sprite_set_velocity(result.enemy_sprite, result.velocity);
    sprite_set_scale(result.enemy_sprite, 0.3);
    return result;
}

void update_enemy(enemy &enemy_to_update)
{
    update_sprite(enemy_to_update.enemy_sprite);
    update_sprite_animation(enemy_to_update.enemy_sprite);
}