#include "Cub.h"

int	count_alloc_size(fd)
{
	int size;
	char *s;

	size = 0;
	s = NULL;
	fd = open("/Users/idouni/Desktop/789/map.Cub", O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while ((s = get_next_line(fd)))
	{
		free(s);
		s = NULL;
		size++;
	}
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
	return (size+=1);
}


char **parse_file(t_collector **collector, int argc, char const *argv[])
{
	int	fd;
	char **map;
	char *s;
	int i;

	i = 0;
	fd = 0;
	map = NULL;
	if (argc && argv[0])   //to_prot
	{
		map = h_malloc(collector, (count_alloc_size(fd) * sizeof(char *)), map);
		fd = open("/Users/idouni/Desktop/789/map.Cub", O_RDONLY);
		if (fd == -1)
			exit(EXIT_FAILURE);
		while((s = get_next_line(fd)))
		{
			map[i] = ft_mstrdup(collector, s);
			free(s);
			s = NULL;
			i++;
		}
		map[i] = NULL;
		// i = 0;
		// while(*map)
		// 	printf("%s\n", *(map)++);
		return (map);
	}
	exit(EXIT_FAILURE);
}

void 	draw_player(t_vars *vars, int px, int py)
{
	int i, j;
	t_data 		*p_img;
	
	p_img = new_image(vars);
	int x = 895 + px;
	int y = 345 + py;
	
	i = 0;
	j = 0;
	while(i < 10)
	{
		while(j < 10)
		{
			my_mlx_pixel_put(vars->map_ptr, x + i, y + j, BLUE);
			j++;
		}
		i++;
		j = 0;
	}
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win,vars->map_ptr->img_ptr, 0, 0);
}


int main(int argc, char const *argv[])
{
	t_collector *collector;
	t_img_collector *img_collector;
	t_vars 		*vars;
	
	collector = NULL;
	img_collector = NULL;

	vars = NULL;
	vars = h_malloc(&collector, sizeof(t_vars), vars);
	vars->img_collector = &img_collector;
	vars->collector = &collector;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Cub");
    vars->map = parse_file(&collector, argc, argv);
	if(!vars->mlx || !vars->win)
	{
		write (2, "\033[0;32mMLX_FAILED\033[0;37m\n", 29);
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector);
		exit (1);
	}
	draw_2d_map(vars);
	draw_player(vars, 0, 0);

	mlx_hook(vars->win, 17, 0, ft_ext, vars);
	mlx_hook(vars->win, 2, 1L << 0, handler, vars);
	mlx_loop(vars->mlx);
	return 0;
}
