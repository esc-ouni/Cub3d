/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/28 00:09:45 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void	free_whats_allocated(t_collector **collector)
{
	t_collector	*head;

	head = *collector;
	free_tmp(collector);
	free_ntmp(collector);
	if (head)
	{
		free(head);
		head = NULL;
	}
	exit(0);
}

void	ft_collectorclear(t_collector **collector, t_player *plyr, t_flag flag)
{
	t_collector	*head;

	head = *(plyr->v->collector);
	if (!plyr || !plyr->v->collector)
		return ;
	if (flag == TMP)
		free_tmp(plyr->v->collector);
	else if (flag == NTMP)
		free_ntmp(plyr->v->collector);
	if (flag == ALL)
	{
		if (collector)
			free_whats_allocated(plyr->v->collector);
		destroy_fix_imges(plyr);
		free_tmp(plyr->v->collector);
		free_ntmp(plyr->v->collector);
		if (head)
		{
			free(head);
			head = NULL;
		}
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
