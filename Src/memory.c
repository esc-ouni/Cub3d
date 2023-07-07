/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:54:17 by idouni            #+#    #+#             */
/*   Updated: 2023/07/07 12:05:11 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

t_data	*new_image_from_xpm(t_player *player, char *file_dstination)
{
	void 	*p;
	t_data			*img;
	int 	width,height;

	img = NULL;
	img = h_malloc(player->vars->collector, sizeof(t_data), img, NTMP);
	p = mlx_xpm_file_to_image(player->vars->mlx, file_dstination, &width, &height);
	if (!p)
		exit_with_err(player->vars->collector, MLX);
	img->img_ptr = p;
	img->img_addr = mlx_get_data_addr(img->img_ptr, &(img->byte_pixel), &(img->size_line), &(img->endian));
	img->byte_pixel /= 8;
	return (img);
}

t_data	*new_image(t_vars *vars, int width, int height, t_flag type)
{
	void			*p;
	t_data			*img;

	img = NULL;
	img = h_malloc(vars->collector, sizeof(t_data), img, type);
	p = mlx_new_image(vars->mlx, width, height);
	if (!p)
		exit_with_err(vars->collector, MLX);
	img->img_ptr = p;
	img->img_addr = mlx_get_data_addr(img->img_ptr, &(img->byte_pixel), &(img->size_line), &(img->endian));
	img->byte_pixel /= 8;
	return (img);
}

void	debug(void)
{
	printf("\x1B[32m");
	printf("\nDEBUG OK\n");
	printf("\x1B[0m");
}

void	tmp_alloc(t_collector **collector, size_t s, void **p)
{
	t_tmp	*n_iter;
	t_tmp	*tmp_c;

	tmp_c = malloc(sizeof(t_tmp));
	(*p) = malloc(s);
	if (!tmp_c || !(*p) || !(*collector))
		exit_with_err(collector, MALLOC);
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
		exit_with_err(collector, MALLOC);
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

void	free_ntmp(t_collector **collector)
{
	t_ntmp	*node1;
	t_ntmp	*n_node1;

	node1 = (*collector)->ntmp_cltr;
	if (!node1)
		return ;
	while (node1)
	{
		n_node1 = node1->next;
		if (node1->ntmp_addr)
			free(node1->ntmp_addr);
		free(node1);
		node1 = n_node1;
	}
	(*collector)->ntmp_cltr = NULL;
}

void	ft_collectorclear(t_collector **collector, t_flag flag)
{
	if (!(*collector) || !collector)
		return ;
	if (flag == TMP)
		free_tmp(collector);
	else if (flag == NTMP)
		free_ntmp(collector);
	else if (flag == ALL)
	{
		free_tmp(collector);
		free_ntmp(collector);
		free((*collector));
		(*collector) = NULL;
		exit(0);
	}
}

void	head_alloc(t_collector **collector)
{
	(*collector) = malloc(sizeof(t_collector));
	if (*collector)
	{
		(*collector)->tmp_cltr = NULL;
		(*collector)->ntmp_cltr = NULL;
	}
}

void	*h_malloc(t_collector **collector, size_t s, void *p, t_flag flag)
{
	if (!(*collector))
		head_alloc(collector);
	if (flag == TMP)
		tmp_alloc(collector, s, &p);
	else if (flag == NTMP)
		ntmp_alloc(collector, s, &p);
	return (p);
}
