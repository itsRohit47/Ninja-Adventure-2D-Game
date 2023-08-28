#include "splashkit.h"
#include "NinjaAdventure.h"
#include "player.h"
#include "surfaces.h"
#include "powerup.h"
#include "enemy.h"

using namespace std;

#define SCREEN_BORDER 500
#define PLAYER_SPEED 10.0

int main()
{
    open_window("Ninja adventure", 1049, 600);
    load_resources();
    game_data game = new_game();


    // add the surfaces and the mosnter to the game
    add_surface(game);
    add_enemy(game);


    while (not quit_requested()) // loop until not quit
    {
        process_events();
        handle_input(game.player);
        update_game(game);
        draw_game(game);
        if (game.quit == true)
        {
            break;
        }
    }
    return 0;
}