/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:17 by idouni            #+#    #+#             */
/*   Updated: 2023/07/31 20:14:18 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_data	*new_image_from_xpm(t_player *plyr, char *file_dstination)
{
	void	*p;
	t_data	*img;
	int		width;
	int		height;

	img = NULL;
	img = h_malloc(plyr->v->collector, sizeof(t_data), img, NTMP);
	p = mlx_xpm_file_to_image(plyr->v->mlx, file_dstination, \
	&width, &height);
	img->img_ptr = p; 
	if (!p)
		exit_with_err(NULL, XPM);
	img->img_addr = mlx_get_data_addr(img->img_ptr, &(img->byte_pixel), \
	&(img->size_line), &(img->endian));
	img->byte_pixel /= 8;
	return (img);
}

t_data	*new_image(t_player *plyr, int width, int height, t_flag type)
{
	void			*p;
	t_data			*img;

	img = NULL;
	img = h_malloc(plyr->v->collector, sizeof(t_data), img, type);
	p = mlx_new_image(plyr->v->mlx, width, height);
	if (!p)
		exit_with_err(NULL, MLX);
	img->img_ptr = p;
	img->img_addr = mlx_get_data_addr(img->img_ptr, &(img->byte_pixel), \
	&(img->size_line), &(img->endian));
	img->byte_pixel /= 8;
	return (img);
}

void	tmp_alloc(t_collector **collector, size_t s, void **p)
{
	t_tmp	*n_iter;
	t_tmp	*tmp_c;

	tmp_c = malloc(sizeof(t_tmp));
	(*p) = malloc(s);
	if (!tmp_c || !(*p) || !(*collector))
		exit_with_err(NULL, MALLOC);
	tmp_c->tmp_addr = (*p);
	if (!((*collector)->tmp_cltr))
		((*collector)->tmp_cltr) = tmp_c;
	else
	{
		n_iter = (*collector)->tmp_cltr;
		while (n_iter->next)
			n_iter = n_iter->next;
		n_iter->next = tmp_c;
	}
	tmp_c->next = NULL;
}

void	ntmp_alloc(t_collector **collector, size_t s, void **p)
{
	t_ntmp	*n_iter1;
	t_ntmp	*ntmp_c;

	ntmp_c = malloc(sizeof(t_ntmp));
	(*p) = malloc(s);
	if (!ntmp_c || !(*p) || !(*collector))
		exit_with_err(NULL, MALLOC);
	ntmp_c->ntmp_addr = (*p);
	if (!((*collector)->ntmp_cltr))
		((*collector)->ntmp_cltr) = ntmp_c;
	else
	{
		n_iter1 = (*collector)->ntmp_cltr;
		while (n_iter1->next)
			n_iter1 = n_iter1->next;
		n_iter1->next = ntmp_c;
	}
	ntmp_c->next = NULL;
}

void	free_tmp(t_collector **collector)
{
	t_tmp	*node;
	t_tmp	*n_node;

	node = (*collector)->tmp_cltr;
	if (!node)
		return ;
	while (node)
	{
		n_node = node->next;
		if (node->tmp_addr)
			free(node->tmp_addr);
		free(node);
		node = n_node;
	}
	(*collector)->tmp_cltr = NULL;
}
