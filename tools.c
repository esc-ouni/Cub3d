#include "Cub.h"

int ft_ext(t_vars *vars)
{
	ft_destroy_all_images(vars);
	ft_collectorclear(vars->collector);
	exit(0);
}

int	handler(int key, t_vars *vars)
{
	static int px;
	static int py;
	static int r = 10;

	if (key == 53 || key == 17)
	{
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector);
		exit(0);
	}
	// else if (key == K_UP)
	// 	move_up(vars);
	// else if (key == K_DN)
	// 	move_dn(vars);
	// else if (key == K_R)
	// 	move_rg(vars);
	// else if (key == K_L)
	// 	move_lf(vars);
	else if (key == M_UP)
		draw_player(vars, px, (py -= r));
	else if (key == M_DN)
		draw_player(vars, px, (py += r));
	else if (key == M_LF)
		draw_player(vars, (px -= r), py);
	else if (key == M_RG)
		draw_player(vars, (px += r), py);
	
	return(0);
}

// void	move_up(t_vars *vars)
// {
// }
// void	move_dn(t_vars *vars)
// {
// }
// void	move_rg(t_vars *vars)
// {
// }

// void	move_lf(t_vars *vars)
// {
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	(void)color;
	char *tmp;

	tmp = data->img_addr;
	if(!tmp)
		exit(EXIT_FAILURE);
	tmp = tmp + (y * data->size_line) + ((data->byte_pixel) * x);
	*(int *)tmp = color;
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
	(ft_strlen(s1) + 1), s);
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void	draw_in_image(t_vars *vars, int r)
{
	int t = 0;
	int i = 0;
	int k = 0;
	int x = 0;
	int p = 0;
	int y = 0;
	int l = 0x60BADD;
	int lr = 598642;
	t_data		*img;

	img = new_image(vars);
	if(r)
	{
		l = 598642;
		lr = 0x60BADD;
	}
	while(x < WIDTH)
	{
		while(y < HEIGHT)
		{
			while (i)
			{
				my_mlx_pixel_put(img, x, p, lr);
				i--;
				p++;
			}
			while(y < HEIGHT)
			{
				my_mlx_pixel_put(img, x, y, l);
				y++;
			}
		}
		x++;
		p = 0;
		y = 0;
		y += k;
		i += k;
		k++;
		if (k == 800)
		{
			t = l;
			l = lr;
			lr = t;
			k = 0;
		}
	}
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img_ptr, 0, 0);
}