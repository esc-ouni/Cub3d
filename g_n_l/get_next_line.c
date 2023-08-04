/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:32:45 by idouni            #+#    #+#             */
/*   Updated: 2023/07/27 21:41:38 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = str_alloc(fd, buffer);
	if (!buffer)
		return (NULL);
	line = line_extract(buffer);
	buffer = r_reset(buffer);
	return (line);
}

char	*line_extract(char *buffer)
{
	int		i;
	int		i2;
	char	*new;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	i2 = i;
	while (buffer[i] != '\n' && buffer[i])
		new[i2++] = buffer[i++];
	new[i2] = '\0';
	return (new);
}
