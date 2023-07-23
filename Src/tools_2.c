/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:41 by idouni            #+#    #+#             */
/*   Updated: 2023/07/23 18:56:20 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

// Global variables
int frameCount = 0;
int lastFrameTime = 0;

// Function to update and render the scene
void updateAndRenderScene(t_player *plyr)
{
	// Put your scene update and rendering logic here
	update_params(plyr);
	// update_scene(plyr);
	
	// // Increment frame count
	frameCount++;

	// Get the current time in milliseconds
	int currentTime = (int) (clock() * 1000 / CLOCKS_PER_SEC);

	// Calculate time difference from the last frame
	int deltaTime = currentTime - lastFrameTime;

	// Update the title of the window with the current FPS
	char fpsString[20];
	// printf("")
	sprintf(fpsString, "FPS: %.2f", 1000.0 / deltaTime);
	mlx_string_put(plyr->v->mlx, plyr->v->win, WIDTH - 150, 10, GREEN, fpsString);
	// printf("")

	// Update the last frame time
	lastFrameTime = currentTime;
}

//######################

int darkenColor(int color, int amount)
{
	int r = 0;
	int g = 0;
	int b = 0;

	b |= (unsigned char)color;
	color >>= 8;
	g |= (unsigned char)color;
	color >>= 8;
	r |= (unsigned char)color;
	b -= amount;
	r -= amount;
	g -= amount;
	if (b < 0)
		b = 0;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	color = 0;
	color |= r;
	color <<= 8;
	color |= g;
	color <<= 8;
	color |= b;
	return (color);
}

char	*get_texture(t_player *plyr, t_ray ray)
{
	char	*s;

	s = NULL;
	if (ray.side == HORZ_D)
		s = plyr->v->dn->img_addr;
	else if (ray.side == HORZ_U)
		s = plyr->v->up->img_addr;
	else if (ray.side == VERT_R)
		s = plyr->v->rg->img_addr;
	else if (ray.side == VERT_L)
		s = plyr->v->lf->img_addr;
	return (s);
}

int	get_color_from_tex(t_player *plyr, char *s, t_ray ray)
{
	int		color;
	char	*tmp;

	if (ray.tex_y >= BLOCK || ray.tex_x >= BLOCK)
		return (0);
	tmp = (s + (ray.tex_y * plyr->v->lf->size_line) + \
	(ray.tex_x * plyr->v->lf->byte_pixel));
	if (tmp)
	{
		color = *(int *)tmp;
		color = darkenColor(color, (float )(ray.length * 255)/ (BLOCK * 40));
		return (color);
	}
	return (0);
}

void	draw_wall_S(t_player *plyr, t_data *p_img, t_ray ray, int x_index)
{
	int		i;
	int		start;
	float	w_heig;

	w_heig = HEIGHT / (ray.length * trigo(ray.angle - plyr->angle, COS)) * \
	(BLOCK * 1.7);
	start = (HEIGHT / 2) - (w_heig / 2);
	i = 0;
	while (i < w_heig)
	{
		if (start + i > 0 && start + i < HEIGHT)
		{
			ray.tex_y = i * (BLOCK / w_heig);
			plyr->color = get_color_from_tex(plyr, get_texture(plyr, ray), ray);
			plyr->t_img = p_img;
			my_mlx_pixel_put(plyr, x_index, start + i, plyr->color);
		}
		if (start + i >= HEIGHT)
			return ;
		i++;
	}
}

void	draw_3d_map(t_player *plyr, t_data *p_img, t_ray *ray)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		draw_wall_S(plyr, p_img, ray[i], i);
		i++;
	}
}

t_data	*ft_transparency(t_player *plyr, t_data *p_img, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	plyr->t_img = p_img;
	while (i < width)
	{
		while (j < height)
		{
			my_mlx_pixel_put(plyr, i, j, TRANS);
			j++;
		}
		i++;
		j = 0;
	}
	return (p_img);
}

void	destroy_fix_imges(t_player *plyr)
{
	mlx_destroy_image(plyr->v->mlx, plyr->v->dn->img_ptr);
	mlx_destroy_image(plyr->v->mlx, plyr->v->rg->img_ptr);
	mlx_destroy_image(plyr->v->mlx, plyr->v->lf->img_ptr);
	mlx_destroy_image(plyr->v->mlx, plyr->v->up->img_ptr);
	mlx_destroy_image(plyr->v->mlx, plyr->v->fix_img->img_ptr);
	mlx_destroy_image(plyr->v->mlx, plyr->v->m_fix_img->img_ptr);
}

void	destroy_prev_imges(t_player *plyr)
{
	int	i;

	i = 0;
	while (plyr->p[i])
	{
		mlx_destroy_image(plyr->v->mlx, plyr->p[i]);
		plyr->p[i] = NULL;
		i++;
	}
}

void	update_params(t_player *plyr)
{
	if (plyr->w == 1)
		check_collision(plyr, plyr->mv_sp * trigo(plyr->angle, COS), \
		plyr->mv_sp * trigo(plyr->angle, SIN));
	else if (plyr->w == -1)
		check_collision(plyr, -(plyr->mv_sp * trigo(plyr->angle, COS)), \
		-(plyr->mv_sp * trigo(plyr->angle, SIN)));
	else if (plyr->d == 1)
		check_collision(plyr, (plyr->mv_sp / 2) * trigo(up_degree(plyr->angle, \
		90), COS), (plyr->mv_sp / 2) * trigo(up_degree(plyr->angle, 90), SIN));
	else if (plyr->d == -1)
		check_collision(plyr, (plyr->mv_sp / 2) * trigo(up_degree(plyr->angle, \
		-90), COS), (plyr->mv_sp / 2) * \
		trigo(up_degree(plyr->angle, -90), SIN));
	else if (plyr->rl == 1)
		update_degree(plyr, -R_AN);
	else if (plyr->rl == -1)
		update_degree(plyr, R_AN);
	// else
	//     return ;
	update_scene (plyr);
}

void	show_the_map(t_player *plyr, t_data	*p_r_img)
{
	mlx_put_image_to_window(plyr->v->mlx, plyr->v->win, \
	plyr->v->m_fix_img->img_ptr, 0, 0);
	mlx_put_image_to_window(plyr->v->mlx, plyr->v->win, p_r_img->img_ptr, 0, 0);
}

void	update_scene(t_player *plyr)
{
	t_data	*p_img;
	t_data	*p_r_img;

	destroy_prev_imges(plyr);
	p_img = new_image(plyr->v, WIDTH, HEIGHT, TMP);
	p_r_img = new_image(plyr->v, WIDTH, HEIGHT, TMP);
	p_img = ft_transparency(plyr, p_img, WIDTH, HEIGHT);
	p_r_img = ft_transparency(plyr, p_r_img, WIDTH, HEIGHT);
	draw_player(plyr, p_r_img);
	plyr->ray = cast_rays(plyr, plyr->ray);
	draw_3d_map(plyr, p_img, plyr->ray);
	mlx_clear_window(plyr->v->mlx, plyr->v->win);
	mlx_put_image_to_window(plyr->v->mlx, plyr->v->win, \
	plyr->v->fix_img->img_ptr, 0, 0);
	mlx_put_image_to_window(plyr->v->mlx, plyr->v->win, p_img->img_ptr, 0, 0);
	if (plyr->m)
		show_the_map(plyr, p_r_img);
	plyr->p[0] = p_img->img_ptr;
	plyr->p[1] = p_r_img->img_ptr;
	plyr->p[2] = NULL;
	ft_collectorclear(plyr->v->collector, TMP);
}

float  draw_ray(t_player *plyr, t_ray *ray)
{
	plyr->vec1 = find_vertical_iterset(plyr, ray, plyr->vec1);
	plyr->vec2 = find_horizontal_iterset(plyr, ray, plyr->vec2);
	ray->v_d_inter = sqrt(ft_pow(plyr->vec1->x - plyr->p_x) + ft_pow(plyr->vec1->y - plyr->p_y));
	ray->h_d_inter = sqrt(ft_pow(plyr->vec2->x - plyr->p_x) + ft_pow(plyr->vec2->y - plyr->p_y));
	if (ray->v_d_inter < ray->h_d_inter)
	{
		if ((ray->angle <= 2 * M_PI && ray->angle > 3 * M_PI / 2) || (ray->angle >= 0 && ray->angle < M_PI / 2))
			ray->side = VERT_R;
		else
			ray->side = VERT_L;
		ray->tex_x = (int)plyr->vec1->y % BLOCK;
		ray->length = ray->v_d_inter;
	}
	else
	{
		if (ray->angle > 0 && ray->angle < M_PI)
			ray->side = HORZ_D;
		else
			ray->side = HORZ_U;
		ray->tex_x = (int)plyr->vec2->x % BLOCK;
		ray->length = ray->h_d_inter;
	}
	return 1;
}

t_ray *cast_rays(t_player *plyr, t_ray *ray)
{
	int i = 0;
	plyr->t_angle = up_degree(plyr->angle, -30);

	while (i < WIDTH)
	{
		ray[i].angle = plyr->t_angle;
		ray[i].t1 = trigo(ray[i].angle, TAN);
		ray[i].t2 = trigo((2 * M_PI) - ray[i].angle, TAN);
		draw_ray(plyr, &ray[i]);
		plyr->t_angle = up_degree(plyr->t_angle, plyr->f_angle);
		i++;
	}
	return (&(ray[0]));
}

int wall_hit_hup(t_player *plyr, int x, int y)
{
	int m_y = ((y)/BLOCK) - 1;
	int m_x = ((x)/BLOCK);

	if (m_x < 0|| m_y < 0)
		return 1;
	if (m_y >= plyr->v->m_h || m_x >= ft_strlen(plyr->v->map[m_y]))
		return 1;
	if (plyr->v->map[m_y][m_x] != '1')
		return (0);
	return (1);
}

int wall_hit_hdn(t_player *plyr, int x, int y)
{
	int m_y = ((y)/BLOCK);
	int m_x = ((x)/BLOCK);

	if (m_x < 0|| m_y < 0)
		return 1;
	if (m_y >= plyr->v->m_h || m_x >= ft_strlen(plyr->v->map[m_y]))
		return 1;
	if (plyr->v->map[m_y][m_x] != '1')
		return (0);
	return (1);
}

int wall_hit_vrg(t_player *plyr, int x, int y)
{
	int m_y = ((y)/BLOCK);
	int m_x = ((x)/BLOCK);

	if (m_x < 0|| m_y < 0)
		return 1;
	if (m_y >= plyr->v->m_h || m_x >= ft_strlen(plyr->v->map[m_y]))
		return 1;
	if (plyr->v->map[m_y][m_x] != '1')
		return (0);
	return (1);
}

int wall_hit_vlf(t_player *plyr, int x, int y)
{
	int m_y = ((y)/BLOCK);
	int m_x = ((x)/BLOCK) - 1;

	if (m_x < 0|| m_y < 0)
		return 1;
	if (m_y >= plyr->v->m_h || m_x >= ft_strlen(plyr->v->map[m_y]))
		return 1;
	if (plyr->v->map[m_y][m_x] != '1')
		return (0);
	return (1);
}

t_vector *h_dn_iterset(t_player *plyr, t_ray *ray, t_vector *vector)
{
	ray->dy = -BLOCK;
	ray->dx = (BLOCK / ray->t2);
	vector->y = floor(plyr->p_y / BLOCK) * BLOCK;
	vector->x = plyr->p_x + (plyr->p_y - vector->y) / ray->t2;
	while (!wall_hit_hup(plyr, (int)vector->x, (int)vector->y))
	{
		vector->x += ray->dx;
		vector->y += ray->dy;
	}
	return vector;
}

t_vector *h_up_iterset(t_player *plyr, t_ray *ray, t_vector *vector)
{
	ray->dy = BLOCK;
	ray->dx = (ray->dy / ray->t1);
	vector->y = (ceil(plyr->p_y / BLOCK) * BLOCK);
	vector->x = plyr->p_x + ((vector->y - plyr->p_y) / ray->t1);
	while (!wall_hit_hdn(plyr, (int)vector->x, (int)vector->y))
	{
		vector->y += ray->dy;
		vector->x += ray->dx;
	}
	return vector;
}

t_vector *find_horizontal_iterset(t_player *plyr, t_ray *ray, t_vector *vector)
{
	if ((ray->angle > 0 && ray->angle < M_PI))
		vector = h_up_iterset(plyr, ray, vector);
	else if (ray->angle > M_PI && ray->angle < 2 * M_PI)
		vector = h_dn_iterset(plyr, ray, vector);
	return vector;
}

t_vector	*h_rg_iterset(t_player *plyr, t_ray *ray, t_vector *vector)
{
	ray->dx = BLOCK;
	ray->dy = ray->dx * ray->t1;
	vector->x = (ceil(plyr->p_x/ BLOCK) * BLOCK);
	vector->y = plyr->p_y + ((vector->x - plyr->p_x) * ray->t1);
	while (!wall_hit_vrg(plyr, (int)vector->x, (int)vector->y))
	{
		vector->x += ray->dx;
		vector->y += ray->dy;
	}
	return (vector);
}

t_vector	*h_lf_iterset(t_player *plyr, t_ray *ray, t_vector *vector)
{
	ray->dx = -BLOCK;
	ray->dy = BLOCK * ray->t2;
	vector->x = (floor(plyr->p_x / BLOCK) * BLOCK);
	vector->y = plyr->p_y - ((vector->x - plyr->p_x) * ray->t2);
	while (!wall_hit_vlf(plyr, (int)vector->x, (int)vector->y))
	{
		vector->x += ray->dx;
		vector->y += ray->dy;
	}
	return (vector);
}

t_vector *find_vertical_iterset(t_player *plyr, t_ray *ray, t_vector *vector)
{
	if (((ray->angle > (3 * (M_PI / 2))) && (ray->angle <= 2 * (M_PI))) || (((ray->angle >= 0) && (ray->angle < (M_PI / 2)))))
		vector = h_rg_iterset(plyr, ray, vector);
	else if ((ray->angle > (M_PI / 2)) || (ray->angle < 3 * (M_PI / 2)))
		vector = h_lf_iterset(plyr, ray, vector);
	return (vector);
}
