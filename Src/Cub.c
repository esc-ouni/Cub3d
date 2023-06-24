#include "Cub.h"

int main(int argc, char const *argv[])
{
	t_player 		*player;

	player = init(argc, argv);
	update_scene(player);
	hooks(player);
	return 0;
}
