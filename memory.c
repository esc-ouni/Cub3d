#include "Cub.h"

// void	*h_malloc(t_collector **collector, size_t s, void *p)
// {
// 	t_collector	*tmp;
// 	t_collector	*new_node;

// 	new_node = malloc(sizeof(t_collector));
// 	p = malloc(s);
// 	if (!new_node || !p)
// 	{
// 		write (2, "\033[0;32mMALLOC_FAILED\033[0;37m\n", 29);
// 		ft_collectorclear(collector);
// 		exit (1);
// 	}
// 	new_node->addr = p;
// 	// printf("alloc     : %p\n", p);
// 	if (!(*collector))
// 	{
// 		*collector = new_node;
// 		new_node->next = NULL;
// 	}
// 	else
// 	{
// 		tmp = *collector;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new_node;
// 		new_node->next = NULL;
// 	}
// 	return (p);
// }



// void	ft_collectorclear(t_collector **collector)
// {
// 	t_collector	*node;
// 	t_collector	*n_node;

// 	if (!(*collector) || !collector)
// 		return ;
// 	node = *collector;
// 	while (node)
// 	{
// 		n_node = node->next;
// 		if (node->addr)
// 		{
// 			// printf("free      : %p\n", node->addr);
// 			free(node->addr);
// 		}
// 		free(node);
// 		node = NULL;
// 		node = n_node;
// 	}
// 	*collector = NULL;
// 	// system(" leaks Cub | grep \"leaks\" | awk '{print $4\" \"$3}' | grep \"leaks \" ");
// }

t_data		*new_image(t_vars *vars)
{
	void			*p;
	t_img_collector	*tmp;
	t_img_collector	*new_node;
	t_data		*img;

	img = NULL;
	img = h_malloc(vars->collector, sizeof(t_data), img, NTMP);
	new_node = NULL;
	p = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	new_node = h_malloc(vars->collector, sizeof(t_img_collector), new_node, NTMP);
	if (!p)
	{
		write (2, "\033[0;32mMLX_NEW_IMAGE_FAILED\033[0;37m\n", 29);
		ft_destroy_all_images(vars);
		ft_collectorclear(vars->collector, ALL);
		exit (1);
	}
	new_node->img_addr = p;
	// printf("new image : %p\n", new_node->img_addr);
	if (!(*(vars->img_collector)))
	{
		*(vars->img_collector) = new_node;
		new_node->next = NULL;
	}
	else
	{
		tmp = *(vars->img_collector);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->next = NULL;
	}
	img->img_ptr = p;
	img->img_addr = mlx_get_data_addr(img->img_ptr, &(img->byte_pixel), &(img->size_line), &(img->endian));
	img->byte_pixel /= 8;
	return (img);
}

void	ft_destroy_all_images(t_vars *vars)
{
	t_img_collector	**collector;
	t_img_collector	*node;

	if (vars->win && vars->mlx)
		mlx_destroy_window(vars->mlx, vars->win);
	collector = vars->img_collector;
	if (!(*collector) || !collector)
		return ;
	node = *collector;
	while (node)
	{
		if (node->img_addr)
		{
			// printf("des image : %p\n", node->img_addr);
			mlx_destroy_image(vars->mlx, node->img_addr);
		}
		node = node->next;
	}
	*collector = NULL;
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
	{
		write (2, "\033[0;32mMALLOC_FAILED\033[0;37m\n", 29);
		ft_collectorclear(collector, ALL);
		exit (1);
	}
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
	{
		write (2, "\033[0;32mMALLOC_FAILED\033[0;37m\n", 29);
		ft_collectorclear(collector, ALL);
		exit (1);
	}
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
