#include "splashkit.h"
#include "player.h"
#define SCREEN_BORDER 160
#define PLAYER_SPEED 10

player_data new_player()
{
    set_camera_x(0);
    player_data result;
    result.player_sprite = create_sprite(bitmap_named("idle"), animation_script_named("anim"));
    sprite_add_layer(result.player_sprite, bitmap_named("run"), "RUN");
    // sprite_add_layer(result.player_sprite, bitmap_named("attack"), "ATTACK");
    sprite_hide_layer(result.player_sprite, 1);
    sprite_hide_layer(result.player_sprite, 2);
    sprite_start_animation(result.player_sprite, 0);
    result.life = 5;
    result.xp = 0.04;
    result.shield = 0.44;
    result.time = 1.0;
    result.next_level = 0.0;
    result.monsters_left = 3;
    result.kill = 100;
    sprite_set_y(result.player_sprite, camera_y() - 165);
    sprite_set_scale(result.player_sprite, 0.2);
    write_line(sprite_y(result.player_sprite));
    write_line(sprite_x(result.player_sprite));
    return result;
}

void hide_all_layers(player_data &player)
{
    sprite_hide_layer(player.player_sprite, 0);
    sprite_hide_layer(player.player_sprite, 1);
    sprite_hide_layer(player.player_sprite, 2);
}

void handle_input(player_data &player)
{

    // Handle movement - rotating left/right and moving forward/back
    float x = sprite_x(player.player_sprite);
    float y = sprite_y(player.player_sprite);
    if (sprite_y(player.player_sprite) < 260)
    {
        if (key_down(LEFT_KEY))
        {
            sprite_set_x(player.player_sprite, x - PLAYER_SPEED);
        }
        if (key_down(RIGHT_KEY))
        {
            hide_all_layers(player);
            sprite_show_layer(player.player_sprite, 1);
            sprite_set_x(player.player_sprite, x + PLAYER_SPEED);
        }

        if (key_released(RIGHT_KEY))
        {
            hide_all_layers(player);
            sprite_show_layer(player.player_sprite, 0);
        }

        if (key_down(UP_KEY))
        {
            sprite_set_y(player.player_sprite, y - 15);
        }
    }
}

void update_player(player_data &player_to_update)
{
    update_sprite(player_to_update.player_sprite);
    sprite_set_dy(player_to_update.player_sprite, 5);
    update_sprite_animation(player_to_update.player_sprite);

    // Test edge of screen boundaries to adjust the camera
    double left_edge = camera_x() + SCREEN_BORDER + 200;
    double right_edge = left_edge - 400 + screen_width() - 2 * SCREEN_BORDER;
    double top_edge = camera_y() + SCREEN_BORDER;
    double bottom_edge = top_edge + screen_height() - 2 * SCREEN_BORDER;

    // Get the center of the player
    point_2d sprite_center = center_point(player_to_update.player_sprite);

    // Test if the player is outside the area and move the camera
    // the player will appear to stay still and everything else
    // will appear to move :)

    // Test left/right of screen
    if (sprite_center.x < left_edge)
    {
        move_camera_by(sprite_center.x - left_edge, 0);
    }
    if (sprite_center.x > right_edge)
    {
        move_camera_by(sprite_center.x - right_edge, 0);
    }
    if (sprite_center.y > bottom_edge)
    {
        sprite_set_dy(player_to_update.player_sprite, 0);
    }
    if (player_to_update.time > 0.05)
    {
        player_to_update.time -= 0.000278;
    }
    if (player_to_update.shield > 0.05)
    {
        player_to_update.shield -= 0.001278;
    }
    if (player_to_update.xp > 0.95)
    {
        player_to_update.xp -= 0.00278;
    }
}
