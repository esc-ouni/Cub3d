/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/08/04 14:52:31 by idouni           ###   ########.fr       */
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
		// printf("%p\n", node1->ntmp_addr);
		// printf("%p\n", node1);
		free(node1->ntmp_addr);
		free(node1);
		node1 = n_node1;
	}
	(*collector)->ntmp_cltr = NULL;
}

void	ft_collectorclear(t_collector **collector, t_flag flag)
{
	// printf("\n\ndestroy :\n");
	if (flag == TMP)
		free_tmp(collector);
	else if (flag == NTMP)
		free_ntmp(collector);
	else if (flag == ALL)
	{
		free_tmp(collector);
		free_ntmp(collector);
		if (*(collector))
		{
			// printf("the last add: %p\n", (*collector));
			free(*(collector));
			*collector = NULL;
		}
		exit(0);
	}
}

void	head_alloc(t_collector **collector)
{
	(*collector) = malloc(sizeof(t_collector));
	// printf("the first add: %p\n", (*collector));
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
