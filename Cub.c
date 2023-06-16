#include "Cub.h"

int main(int argc, char const *argv[])
{
	t_player 		*player;

	player = init(argc, argv);
	hooks(player);
	return 0;
}
