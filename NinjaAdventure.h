#ifndef NINJA_ADVENTURE
#define NINJA_ADVENTURE

#include "splashkit.h"
#include "player.h"
#include "powerup.h"
#include "surfaces.h"
#include "enemy.h"

// the procedure loads all the resources into the game from the resouce bundle
void load_resources();

// game struct that controls all the game data
struct game_data
{
    player_data player;
    vector<surfaces> surface;
    vector<power_up_data> powerup;
    vector<enemy> enemies;
    int level;
    bool new_level;
    int enemy_health;
    int player_health;
    bool quit;
};

// a function that initialize the game by adding a player into it
game_data new_game();

// it shows the pause screen for the game
void show_level_info(game_data &game);

//  to add surfaces to the game
void add_surface(game_data &game);

//  to push monster to the game
void add_enemy(game_data &game);

//  to add power ups to the game
void add_power_up(game_data &game);

// removes the monster when the player kills it
void remove_enemy(game_data &game, int index);

// apply all the enemy related changes to the game
void apply_enemy(game_data &game, int index);

// this procedure updates all the entities of the game such as player, power ups, surfaces
void update_game(game_data &game);

// this procedure draws all the sprites, background, and other features such as the game HUD
void draw_game(game_data &game);

// this procedure applies the effect of power up on the player based on the powerup kind
void apply_power_up(game_data &game, int index);

// this procedure applies effects of collisions of player with the surface such as shaking it in random axis and drifiting it into the lava
void apply_surface(game_data &game, surfaces &surface, int index);

// this procedure removes the powerups from the game as the player collides with it
void remove_power_up(game_data &game, int index);

// this procedure checks all the collisions of player with the powerups and the surfaces
void check_collisions(game_data &game);

#endif
