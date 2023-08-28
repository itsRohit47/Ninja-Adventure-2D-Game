#ifndef PLAYER
#define PLAYER
#include "splashkit.h"

// entity - player - it has its sprite and other concerned data such as life, time etc.
struct player_data
{
    sprite player_sprite;
    int life;
    double xp;
    double time;
    double shield;
    double next_level;
    int monsters_left;
    int kill;
};

// this function initialize a new player into the game
player_data new_player();

// this procedure update the player related data dynamically as the player progresses
void update_player(player_data &player_to_update);

// this procedure handels keyboard inputs from the user
void handle_input(player_data &player);

#endif
