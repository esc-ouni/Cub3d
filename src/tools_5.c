/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:23:22 by idouni            #+#    #+#             */
/*   Updated: 2023/07/27 20:56:43 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	p_check(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ns_start(char const *s1, char const *set)
{
	size_t		l_f;
	size_t		i;

	i = 0;
	l_f = 0;
	while (s1[i])
	{
		if (p_check(s1[i], set) == 1)
			l_f++;
		else
			break ;
		i++;
	}
	return (l_f);
}

char	*ft_mstrtrim(t_vars *vars, char const *s1, \
char const *set, t_flag flag)
{
	char		*ns;
	size_t		l;
	size_t		l_e;
	size_t		l_f;
	size_t		i;

	ns = NULL;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	l_f = ns_start(s1, set);
	l_e = ft_strlen(s1);
	if (l_f > l_e)
		return (ft_mstrdup(vars->collector, "", TMP));
	l = l_e - l_f + 1;
	ns = (char *)h_malloc(vars->collector, sizeof (char) * (l + 1), ns, flag);
	if (!ns)
		return (0);
	while (l--)
	{
		ns[i] = s1[l_f + i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}

char	*ft_msubstr(t_vars *vars, char const *s, unsigned int \
start, size_t len)
{
	char	*ns;
	size_t	l;

	ns = NULL;
	if (s == NULL)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_mstrdup(vars->collector, "", TMP));
	l = (unsigned int)ft_strlen(s + start);
	if (l < len)
		len = l;
	ns = (char *)h_malloc(vars->collector, sizeof (char) * (len + 1), ns, TMP);
	if (!ns)
		return (NULL);
	ft_strlcpy(ns, s + start, len + 1);
	return (ns);
}
