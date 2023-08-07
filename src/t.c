#include "cub.h"

// void 	leak()
// {
// 	system("leaks a.out");
// }


typedef struct varrr
{
	void *o;
	int *l;
}	t_varrr;

int main(int argc, char const *argv[])
{
	// void	*mlx;
	t_varrr *varrr;
	// void	*xpm;
	// int		width;
	// int		height;

	// atexit(leak);
	// mlx = mlx_init();
	// xpm = mlx_xpm_file_to_image(mlx, "", &width, &height);
	// if (!xpm)
	// 	write(1, "\n\nholllla\n", 11);
	// free(mlx);
	varrr = malloc(sizeof(t_varr));
	printf("%p\n", varrr->l);
	printf("%p\n", varrr->o);
	return 0;
}
