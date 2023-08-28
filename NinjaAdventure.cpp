#include "splashkit.h"
#include "NinjaAdventure.h"
using namespace std;

double x = 20;
double enemy_x = 1000;
double power_up_x = 20;

void load_resources()
{
    load_resource_bundle("game_bundle", "ninja_adventure.txt");
}

game_data new_game()
{
    game_data result;
    result.player = new_player();
    result.level = 1;
    result.new_level = true;
    result.quit = false;
    result.enemy_health = 100;
    result.player_health = 100;
    return result;
}

void show_level_info(game_data &game)
{
    if (game.player.life <= 0 or game.player.time <= 0)
    {
        play_sound_effect("over");
        fill_rectangle(COLOR_BLACK, 0, 0, screen_width(), screen_height(), option_to_screen());
        draw_text("NINJA ADVENTURE", COLOR_WHITE, "font.otf", 60, 200, 100, option_to_screen());
        draw_text("G A M E    O V E R", COLOR_RED, "font.otf", 80, 200, 300, option_to_screen());
        draw_text("Press R to restart", COLOR_BLUE_VIOLET, "font.otf", 25, 400, 500, option_to_screen());
        draw_text("Press Q to quit", COLOR_RED, "font.otf", 25, 600, 500, option_to_screen());

        if (key_typed(R_KEY))
        {
            game.new_level = false;
            stop_sound_effect("over");
            game = new_game();
        }
        if (key_typed(Q_KEY))
        {
            game.quit = true;
        }
        stop_sound_effect("over");
    }
    else
    {
        fill_rectangle(COLOR_BLACK, 0, 0, screen_width(), screen_height(), option_to_screen());
        draw_text("NINJA  A D V E N T U R E", COLOR_WHITE, "font.otf", 60, 50, 10, option_to_screen());
        draw_bitmap("pause", 200, 150, option_scale_bmp(0.6, 0.6, option_to_screen()));
        draw_text("Press Y to continue", COLOR_RED, "font.otf", 25, 600, 500, option_to_screen());
        draw_text("Welcome to level " + to_string(game.level), COLOR_YELLOW, "font.otf", 35, 600, 50, option_to_screen());
        draw_text("Instructions ;) ", COLOR_BLUE_VIOLET, "font.otf", 25, 400, 200, option_to_screen());
        draw_text(" > Kill " + to_string(game.player.monsters_left) + " Monsters ", COLOR_GOLD, "font.otf", 25, 400, 250, option_to_screen());
        draw_text(" > Hold < S P A C E > to kill a monster", COLOR_SILVER, "font.otf", 30, 400, 280, option_to_screen());
        draw_text(" > Remember Time is limited !", COLOR_CRIMSON, "font.otf", 30, 400, 310, option_to_screen());
        draw_text(" > use shield to save the ninja", COLOR_NAVAJO_WHITE, "font.otf", 30, 400, 340, option_to_screen());
        draw_text(" > Kill the bad guy before he takes you out", COLOR_MINT_CREAM, "font.otf", 30, 400, 370, option_to_screen());
        draw_text("Good Luck , my friend ! ", COLOR_GREEN, "font.otf", 25, 400, 460, option_to_screen());
        if (key_down(Y_KEY))
        {
            game.new_level = false;
        }
    }
}

void add_power_up(game_data &game)
{
    if (rnd() < 0.005)
    {
        game.powerup.push_back(new_power_up(power_up_x));
    }
}

void add_enemy(game_data &game)
{
    if (game.level == 1)
    {
        for (int i = 0; i < 300; i++)
        {
            game.enemies.push_back(new_enemy(enemy_x));
        }
    }
    if (game.level == 2)
    {
        for (int i = 0; i < game.level * 300; i++)
        {
            game.enemies.push_back(new_enemy(enemy_x));
        }
    }
}

void add_surface(game_data &game)
{
    for (int i = 0; i < 100; i++)
    {
        game.surface.push_back(new_surface(x, game.level));
    }
}

void draw_hud(const game_data &game)
{

    // draw_rectangle(COLOR_BLACK, 10, 30, 750, 130,option_to_screen());
    draw_text("( " + to_string(game.player_health) + " )", COLOR_RED, "font.otf", 25, screen_width() - 360, 40, option_to_screen());
    for (int i = 0; i < game.player.life; i++)
    {
        draw_bitmap("life", screen_width() - 300 + i * 50 + 10, 0, option_scale_bmp(0.4, 0.4, option_to_screen()));
    }

    if (game.player.next_level <= 1)
    {
        draw_text("M O N S T E R S : " + to_string(game.player.monsters_left) + " ( " + to_string(game.enemy_health) + " ) ", COLOR_RED, "font.otf", 25, screen_width() - 300, 150, option_to_screen());
        draw_bitmap("skull", screen_width() - 400, 30, option_scale_bmp(0.7, 0.7, option_to_screen()));
        draw_bitmap("empty", screen_width() - 300, 70, option_to_screen());
        draw_bitmap("full", screen_width() - 300, 70, option_part_bmp(0, 0, game.player.next_level * bitmap_width("purplebar"), bitmap_height("purplebar"), option_to_screen()));
    }

    if (game.player.shield <= 1)
    {
        draw_bitmap("shield", 0, 5, option_scale_bmp(0.4, 0.4, option_to_screen()));
        draw_bitmap("empty", 70, 35, option_to_screen());
        draw_bitmap("purplebar", 70, 35, option_part_bmp(0, 0, game.player.shield * bitmap_width("purplebar"), bitmap_height("purplebar"), option_to_screen()));
    }
    if (game.player.time <= 1)
    {
        draw_bitmap("time", 0, 45, option_scale_bmp(0.4, 0.4, option_to_screen()));
        draw_bitmap("empty", 70, 75, option_to_screen());
        draw_bitmap("bluebar", 70, 75, option_part_bmp(0, 0, game.player.time * bitmap_width("bluebar"), bitmap_height("bluebar"), option_to_screen()));
    }
    if (game.player.xp <= 1)
    {
        draw_bitmap("xp", 0, 80, option_scale_bmp(0.4, 0.4, option_to_screen()));
        draw_bitmap("empty", 70, 115, option_to_screen());
        draw_bitmap("redbar", 70, 115, option_part_bmp(0, 0, game.player.xp * bitmap_width("redbar"), bitmap_height("redbar"), option_to_screen()));
    }
    if (game.player.shield > 0.05)
    {
        draw_text("SHIELD ACTIVATED", COLOR_PURPLE, "font.otf", 25, 450, 150, option_to_screen());
    }
}

void remove_enemy(game_data &game, int index)
{
    int last_idx;
    last_idx = game.enemies.size() - 1;
    game.enemies[index] = game.enemies[last_idx];
    game.enemies.pop_back();
}

void apply_enemy(game_data &game, int index)
{
    if (game.player.life >= 0)
    {

        if (not(game.player.shield > 0.05))
        {
            game.player.kill -= 2;
            game.player_health -= 2;
            if (game.player.kill <= 0)
            {
                game.player.life -= 1;
                play_sound_effect("bump");
                game.player.kill = 100;
                game.player_health = 100;
            }
        }

        if (key_down(SPACE_KEY))
        {
            game.enemies[index].kill -= 1;
            game.enemy_health -= 1;
            play_sound_effect("killed");
        }
    }
    else
    {
        game.new_level = true;
    }

    if (game.enemies[index].kill == 0)
    {
        remove_enemy(game, index);
        play_sound_effect("killed");
        game.player.monsters_left -= 1;
        game.enemy_health = 100;
        game.player.next_level += 0.20;
        if (game.player.monsters_left == 0)
        {
            game.player.next_level = 0.0;
            game.level += 1;
            game.player.monsters_left += game.level * 7;
            for (int i = game.enemies.size() - 1; i > 0; i--)
            {
                game.enemies.pop_back();
            }
            for (int i = game.surface.size() - 1; i > 0; i--)
            {
                game.surface.pop_back();
            }
            enemy_x = 300;
            add_enemy(game);
            x = 20;
            add_surface(game);
            game.new_level = true;
        }
    }
}

void apply_power_up(game_data &game, int index)
{
    if (game.powerup[index].kind == XP and game.player.xp < 0.90)
    {
        play_sound_effect("powerup");
        game.player.xp += 0.1;
    }
    if (game.powerup[index].kind == SHIELD and game.player.shield < 0.90)
    {
        play_sound_effect("powerup");
        game.player.shield = 1;
    }
    if (game.powerup[index].kind == LIFE)
    {
        if (game.player.life <= 3)
        {
            play_sound_effect("powerup");
            game.player.life += 1;
        }
    }
    if (game.powerup[index].kind == TIME and game.player.time < 0.90)
    {
        game.player.time += 0.1;
    }
}

void apply_surface(game_data &game, surfaces &surface, int index)
{
    vector_2d vilocity_player;
    vilocity_player.y = 0;
    sprite_set_velocity(game.player.player_sprite, vilocity_player);
}

void remove_power_up(game_data &game, int index)
{
    int last_idx;
    last_idx = game.powerup.size() - 1;
    game.powerup[index] = game.powerup[last_idx];
    game.powerup.pop_back();
}

void check_collisions(game_data &game)
{
    for (int i = 0; i < game.powerup.size(); i++)
    {
        if (sprite_collision(game.powerup[i].power_up_sprite, game.player.player_sprite))
        {
            apply_power_up(game, i);
            remove_power_up(game, i);
        }
    }

    for (int i = 0; i < game.surface.size(); i++)
    {
        if (sprite_collision(game.player.player_sprite, game.surface[i].surface_sprite) and (center_point(game.player.player_sprite).y < center_point(game.surface[i].surface_sprite).y - sprite_height(game.surface[i].surface_sprite) / 2))
        {
            apply_surface(game, game.surface[i], i);
        }
    }
    for (int i = 0; i < game.enemies.size(); i++)
    {
        if (sprite_collision(game.player.player_sprite, game.enemies[i].enemy_sprite))
        {
            vector_2d velos;
            velos.x = 0;
            sprite_set_velocity(game.enemies[i].enemy_sprite, velos);

            apply_enemy(game, i);

            if (key_released(SPACE_KEY))
            {
                draw_text("Hold < SPACE > to kill", COLOR_RED, "font.otf", 25, 400, 550, option_to_screen());
            }
        }
    }
}

void update_game(game_data &game)
{
    add_power_up(game);
    check_collisions(game);
    update_player(game.player);

    for (int i = 0; i < game.powerup.size(); i++)
    {
        update_power_up(game.powerup[i]);
    }
    for (int i = 0; i < game.surface.size(); i++)
    {
        update_surface(game.surface[i]);
    }
    for (int i = 0; i < game.enemies.size(); i++)
    {
        update_enemy(game.enemies[i]);
    }
}

void draw_game(game_data &game)
{
    if (game.level == 1)
    {
        draw_bitmap("bg", 0, 0, option_to_screen());
    }

    if (game.level == 2)
    {
        draw_bitmap("bg2", 0, 0, option_to_screen());
    }

    for (int i = 0; i < game.surface.size(); i++)
    {
        draw_sprite(game.surface[i].surface_sprite);
    }

    draw_sprite(game.player.player_sprite);

    for (int i = 0; i < game.powerup.size(); i++)
    {
        draw_sprite(game.powerup[i].power_up_sprite);
    }

    for (int i = 0; i < game.enemies.size(); i++)
    {
        draw_sprite(game.enemies[i].enemy_sprite);
    }

    draw_hud(game);

    if (game.new_level == true)
    {
        show_level_info(game);
    }

    refresh_screen(60);
}