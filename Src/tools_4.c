/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:23:31 by idouni            #+#    #+#             */
/*   Updated: 2023/07/01 20:46:01 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

// static int	pcheck(char c, char const *set)
// {
// 	size_t	i;

// 	i = 0;
// 	while (set[i])
// 	{
// 		if (set[i] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// static int	ns_start(char const *s1, char const *set)
// {
// 	size_t		l_f;
// 	size_t		i;

// 	i = 0;
// 	l_f = 0;
// 	while (s1[i])
// 	{
// 		if (pcheck(s1[i], set) == 1)
// 			l_f++;
// 		else
// 			break ;
// 		i++;
// 	}
// 	return (l_f);
// }

// static int	ns_end(char const *s1, char const *set)
// {
// 	size_t		l_e;
// 	size_t		l;

// 	l_e = ft_strlen(s1) - 1;
// 	l = l_e;
// 	while (l)
// 	{
// 		if (pcheck(s1[l_e], set) == 1)
// 			l_e--;
// 		else
// 			break ;
// 		l--;
// 	}
// 	return (l_e);
// }

// char	*ft_mstrtrim(t_collector **collector, char const *s1, char const *set)
// {
// 	char		*ns;
// 	size_t		l;
// 	size_t		l_e;
// 	size_t		l_f;
// 	size_t		i;

// 	ns = NULL;
// 	i = 0;
// 	if (!s1 || !set)
// 		return (NULL);
// 	l_f = ns_start(s1, set);
// 	l_e = ns_end(s1, set);
// 	if (l_f > l_e)
// 		return (ft_mstrdup(collector, ""));
// 	l = l_e - l_f + 1;
// 	ns = (char *)h_malloc(collector, sizeof (char) * (l + 1), ns);
// 	if (!ns)
// 		return (0);
// 	while (l--)
// 	{
// 		ns[i] = s1[l_f + i];
// 		i++;
// 	}
// 	ns[i] = '\0';
// 	return (ns);
// }

// char	*ft_msubstr(t_collector **collector, char const *s, unsigned int \
// start, size_t len)
// {
// 	char	*ns;
// 	size_t	l;

// 	ns = NULL;
// 	if (s == NULL)
// 		return (NULL);
// 	if (start > (unsigned int)ft_strlen(s))
// 		return (ft_mstrdup(collector, ""));
// 	l = (unsigned int)ft_strlen(s + start);
// 	if (l < len)
// 		len = l;
// 	ns = (char *)h_malloc(collector, sizeof (char) * (len + 1), ns);
// 	if (!ns)
// 		return (NULL);
// 	ft_strlcpy(ns, s + start, len + 1);
// 	return (ns);
// }


// static char	**free_s(char **p, int l)
// {
// 	while (l)
// 	{
// 		free(p[l]);
// 		l--;
// 	}
// 	free(p[0]);
// 	free(p);
// 	return (NULL);
// }

// static size_t	count_str(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	t;
// 	size_t	count;

// 	i = 0;
// 	t = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c && t == 0)
// 		{
// 			t = 1;
// 			count++;
// 		}
// 		else if (s[i] == c)
// 			t = 0;
// 		i++;
// 	}
// 	return (count);
// }

// static size_t	lenfinder(char const *s, char c, int start)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[start + i] || s[start + i] == '\0')
// 	{
// 		if (s[start + i] == c || s[start + i] == '\0')
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

// static char	**ft_msplitp2(t_collector **collector, char **p, \
// char const *s, char const c)
// {
// 	size_t		i;
// 	size_t		l;
// 	size_t		l_s;
// 	size_t		i2;

// 	i = 0;
// 	i2 = 0;
// 	l_s = ft_strlen(s);
// 	while (i < l_s)
// 	{
// 		if (s[i] != c)
// 		{
// 			l = lenfinder(s, c, i);
// 			p[i2] = ft_msubstr(collector, s, i, l);
// 			if (p[i2] == NULL)
// 				return (free_s (p, i2));
// 			i2++;
// 			i += l;
// 		}
// 		i++;
// 	}
// 	p[i2] = NULL;
// 	return (p);
// }

// char	**ft_msplit(t_collector **collector, char const *s, char const c)
// {
// 	size_t		n;
// 	char		**p;

// 	p = NULL;
// 	if (!s)
// 		return (NULL);
// 	n = count_str(s, c);
// 	p = (char **)h_malloc(collector, sizeof (char *) * (n + 1), p);
// 	if (p)
// 	{
// 		p = ft_msplitp2(collector, p, s, c);
// 		return (p);
// 	}
// 	return (NULL);
// }


// char	*ft_mstrdup(t_collector **collector, const char *s1)
// {
// 	size_t	i;
// 	char	*s;

// 	i = 0;
// 	s = NULL;
// 	if (!s1)
// 		return (NULL);
// 	s = (char *)h_malloc(collector, sizeof(char) * (ft_strlen(s1) + 1), s);
// 	while (s1[i] != '\0')
// 	{
// 		s[i] = s1[i];
// 		i++;
// 	}
// 	s[i] = '\0';
// 	return (s);
// }

// char	*ft_mstrjoin(t_collector **collector, char const *s1, char const *s2)
// {
// 	size_t		l1;
// 	size_t		l2;
// 	char		*ns;

// 	ns = NULL;
// 	l1 = ft_strlen(s1);
// 	l2 = ft_strlen(s2);
// 	ns = (char *)h_malloc(collector, sizeof(char) * (l1 + l2 + 1), ns);
// 	if (ns)
// 	{
// 		if (s1)
// 			ft_memmove(ns, s1, l1);
// 		if (s2)
// 			ft_memmove(ns + l1, s2, l2);
// 		ns[l2 + l1] = '\0';
// 		return (ns);
// 	}
// 	return (ns);
// }


