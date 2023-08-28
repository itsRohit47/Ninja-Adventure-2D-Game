#ifndef POWER_UP
#define POWER_UP

#include "splashkit.h"

// the kind of power ups
enum power_up_kind
{
    XP,
    SHIELD,
    LIFE,
    TIME,
};

// entity  - power up, it has its sprite and a kind
struct power_up_data
{
    sprite power_up_sprite;
    power_up_kind kind;
};

// this function returns the bitmap related to the power up in action
bitmap power_up_bitmap(power_up_kind kind);

// this function returns a random power up based on the power up kind and locate it on a random position on the x axis
power_up_data new_power_up(double &x);

// this procedure update the powerup related data dynamically as the player progresses
void update_power_up(power_up_data &power_up_to_update);

#endif
