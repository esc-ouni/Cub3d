/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:41 by idouni            #+#    #+#             */
/*   Updated: 2023/07/24 13:38:05 by idouni           ###   ########.fr       */
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

void	correct(int *b, int *r, int *g)
{
	if ((*b) < 0)
		(*b) = 0;
	if ((*r) < 0)
		(*r) = 0;
	if ((*g) < 0)
		(*g) = 0;
}

int	darken_color(int color, int amount)
{
	int	r;
	int	g;
	int	b;

	amount /= 1.9;
	r = 0;
	g = 0;
	b = 0;
	b |= (unsigned char)color;
	color >>= 8;
	g |= (unsigned char)color;
	color >>= 8;
	r |= (unsigned char)color;
	b -= amount;
	r -= amount;
	g -= amount;
	correct(&b, &r, &g);
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
		color = darken_color(color, (float )(ray.length * 255)/ (BLOCK * 40));
		return (color);
	}
	return (0);
}

void	draw_wall_part(t_player *plyr, t_data *p_img, t_ray ray, int x_index)
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
