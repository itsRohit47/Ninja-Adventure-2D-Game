#ifndef ENEMY
#define ENEMY

#include "splashkit.h"

// the different  monsters in the game
enum enemy_kind
{
    MONSTER1,
    MONSTER2
};

//the monster data
struct enemy
{
    sprite enemy_sprite;
    enemy_kind kind;
    vector_2d velocity;
    int kill;
};

// this function returns the bitmap related to the mosnter
bitmap enemy_bitmap(enemy_kind kind);

// this creates the mosnter for the game
enemy new_enemy(double &x);

// this updates the monster animation and sprite
void update_enemy(enemy &enemy_to_update);

#endif