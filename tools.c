#include "Cub.h"

int ft_ext(t_player *player)
{
	ft_collectorclear(player->vars->collector, ALL);
	exit(0);
}

float 	deg_to_rad(float angle)
{
    angle = (angle * M_PI / 180);
	return (angle);
}

void rotate_vector(t_vector *direction, float angle)
{
	angle = deg_to_rad(angle);
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);

    float new_x = ((direction->x * cos_angle) - (direction->y * sin_angle));
    float new_y = ((direction->x * sin_angle) + (direction->y * cos_angle));

    direction->x = new_x;
    direction->y = new_y;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int i;
	char *tmp;

	tmp = data->img_addr;
	if(!tmp)
		exit(EXIT_FAILURE);
	i = (y * data->size_line) + ((data->byte_pixel) * x);
	// *(unsigned int *)tmp = color;
	tmp[i] = color;
	tmp[i+1] = color >>= 8;
	tmp[i+2] = color >>= 8;
	tmp[i+3] = color >>= 8;
}

char	*ft_mstrdup(t_collector **collector, char *s1)
{
	size_t	i;
	char	*s;

	i = 0;
	s = NULL;
	if (!s1)
		return (NULL);
	s = (char *)h_malloc(collector, sizeof(char) * \
	(ft_strlen(s1) + 1), s, NTMP);
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

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
		map = h_malloc(collector, (count_alloc_size(fd) * sizeof(char *)), map, NTMP);
		fd = open("./map.Cub", O_RDONLY);
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
		return (map);
	}
	exit(EXIT_FAILURE);
}

t_player *init(int argc, char const *argv[])
{
	static t_collector	*collector;
	t_vars 				*vars;
	t_player 			*player;

	
	collector = NULL;
	player = NULL;
	vars = NULL;
	player = h_malloc(&collector, sizeof(t_player), vars, NTMP);
	vars = NULL;
	vars = h_malloc(&collector, sizeof(t_vars), vars, NTMP);
	vars->collector = &collector;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Cub");
    vars->map = parse_file(&collector, argc, argv);
	if(!vars->mlx || !vars->win)
	{
		write (2, "\033[0;32mMLX_FAILED\033[0;37m\n", 29);
		ft_collectorclear(vars->collector, ALL);
		exit (1);
	}
	player->direction = NULL;
	player->vars = vars;
	player->vars->last_img = NULL;
	player->vars->last_img = h_malloc(&collector, sizeof(t_data *), player->vars->last_img, NTMP);
	player->vars->last_img = NULL;
	player->direction = h_malloc(&collector, sizeof(t_vector), player->direction, NTMP);
	player->p_x = 250;
	player->p_y = 250;
	player->direction->x = 1;
	player->direction->y = 0;
	player->angle = 0.0001;
	player->vars->texture = new_image_from_xpm(player, "./texture.xpm");
	return (player);
}

t_data 	*draw_player(t_player *player, t_data *p_img)
{
	int i, j, k, x, y;

	i = -5;
	j = -5; 
	k = 0; 

	x = (int)player->p_x;
	y = (int)player->p_y;
	while(i < 5)
	{
		while(j < 5)
		{
			my_mlx_pixel_put(p_img, x + i, y + j, BLUE);
			j++;
		}
		i++;
		j = -5;
	}
	return (p_img);
}

void hooks(t_player *player)
{
	mlx_hook(player->vars->win, 17, 0, ft_ext, player);
	mlx_hook(player->vars->win, 2, 1L << 0, handler, player);
	mlx_hook(player->vars->win, 6, 0, mouse_movement, player);
	mlx_loop(player->vars->mlx);
}

int check_collision_v2(t_player *player, int x, int y)
{
	int m_y = ((y)/BLOCK);
	int m_x = ((x)/BLOCK);

	if (m_x < 0|| m_y < 0)
		return 0;
	if (m_x > 9|| m_y > 9)
		return 0;
	if (player->vars->map[m_y][m_x] == '0')
		return (1);
	return (0);
}

int check_collision(t_player *player, int x, int y)
{
	int m_y;
	int m_x;

	m_y = ((player->p_y + y)/BLOCK);
	m_x = ((player->p_x + x)/BLOCK);

	if (player->vars->map[m_y][m_x] == '0')
	{
		return (1);
	}	
	return (0);
}

void draw_point(t_player *player, int x, int y)
{
    int i, j;

    i = -2;
    j = -2; 
    while (i < 4)
    {
        while(i < 2)
        {
            while(j < 2)
            {
                mlx_pixel_put(player->vars->mlx, player->vars->win, x + i, y + j, RED);
                j++;
            }
            i++;
            j = -2;
        }
        i++;
    }
}

// void draw_wall_part(t_player *player, t_data *p_img, int color,int x1, int y1, int x2, int y2, int index)
// {
//     int i = 0;

// 	(void)player;
// 	(void)index;
//     float dx = x2 - x1;
//     float dy = y2 - y1;
//     float steps = ft_abs(dy);
// 	if (ft_abs(dx) > ft_abs(dy))
// 		steps = ft_abs(dx);
//     float x_inc = dx / steps;
//     float y_inc = dy / steps;

//     float x = x1;
//     float y = y1;

//     while ( i < steps)
//     {
// 		if (i < 50)
// 		{
// 			color = (player->vars->texture->img_addr[(i * player->vars->texture->size_line) + (index)] << 24) |
// 					(player->vars->texture->img_addr[(i * player->vars->texture->size_line) + (index + 1)] << 16) |
// 					(player->vars->texture->img_addr[(i * player->vars->texture->size_line) + (index + 2)] << 8) |
// 					player->vars->texture->img_addr[(i * player->vars->texture->size_line) + (index + 3)];
// 		}
// 		my_mlx_pixel_put(p_img, (int)x, (int)y, color);
//         x += x_inc;
//         y += y_inc;
//         i++;
//     }
// 		printf("\n\n");

// }


void draw_wall_part(t_player *player, t_data *p_img, int color,int x1, int y1, int x2, int y2, int index,  int amount)
{
	(void)amount;
	(void)player;
	(void)index;
    int i = 0;

	// char *tmp;
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = ft_abs(dy);
	if (ft_abs(dx) > ft_abs(dy))
		steps = ft_abs(dx);
    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = x1;
    float y = y1;

	// tmp = player->vars->texture->img_addr;
	// printf("%d\n", index);
	while ( i < steps)
	{
		// if (i < 50)
		// {
		// 	color = *(int *)(player->vars->texture->img_addr + ((i * player->vars->texture->size_line) + (index * player->vars->texture->byte_pixel)));
		// }
        // color = darkenColor(color, amount);
		my_mlx_pixel_put(p_img, (int)x, (int)y, color);
		x += 0 * x_inc * y_inc;
		y += 1;
		i++;
	}
}

void draw_line(t_player *player, t_data *p_img, int color, int x2, int y2)
{
    int i = 0;

    float dx = x2 - (int)player->p_x;
    float dy = y2 - (int)player->p_y;
    float steps = ft_abs(dy);
	if (ft_abs(dx) > ft_abs(dy))
		steps = ft_abs(dx);
    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = (int)player->p_x;
    float y = (int)player->p_y;

    while ( i < steps)
    {
		my_mlx_pixel_put(p_img, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
        i++;
    }
}

float	ft_pow(float n)
{
	return (n * n);
}
float	ft_abs(float n)
{
	if (n < 0)
		n = -n;
	return (n);
}
