#include "get_next_line.h"

// join and free
char	*ft_gfree(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_gstrjoin(buffer, buf);
	free(buffer);
	return (temp);
}

// delete line find
char	*ft_gnext(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	// find len of first line
	while (buffer[i] && buffer[i] != '\n')
		i++;
	// if eol == \0 return NULL
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	// len of file - len of firstline + 1
	line = ft_gcalloc((ft_gstrlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	// line == buffer
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

// take line for return
char	*ft_gline(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	// if no line return NULL
	if (!buffer[i])
		return (NULL);
	// go to the eol
	while (buffer[i] && buffer[i] != '\n')
		i++;
	// malloc to eol
	line = ft_gcalloc(i + 2, sizeof(char));
	i = 0;
	// line = buffer
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	// if eol is \0 or \n, replace eol by \n
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	// malloc if res dont exist
	if (!res)
		res = ft_gcalloc(1, 1);
	// malloc buffer
	buffer = ft_gcalloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		// while not eof read
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		// 0 to end for leak
		buffer[byte_read] = 0;
		// join and free
		res = ft_gfree(res, buffer);
		// quit if \n find
		if (ft_gstrchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	// error handling
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_gline(buffer);
	buffer = ft_gnext(buffer);
	return (line);
}

char	*ft_gstrjoin(char const *s1, char const *s2)
{
	int		sizetotal;
	char	*res;
	int		i;
	int		j;

	i = 0;
	sizetotal = ft_gstrlen(s1) + ft_gstrlen(s2);
	res = malloc(sizeof(char) * (sizetotal + 1));
	if (!res || !s1 || !s2)
		return (NULL);
	while (s1[i] != 0)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[sizetotal] = 0;
	return (res);
}

char	*ft_gstrchr(const char *string, int searchedChar )
{
	char	*str;

	str = (char *)string;
	while (*str != searchedChar && *str != 0)
		str++;
	if (*str == searchedChar)
		return (str);
	else
		return (NULL);
}

void	ft_gbzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_gcalloc(size_t elementCount, size_t elementSize)
{
	char	*res;

	res = malloc(elementSize * elementCount);
	if (!res)
		return (NULL);
	ft_gbzero(res, elementSize * elementCount);
	return (res);
}

size_t	ft_gstrlen(const char *theString)
{
	int	i;

	i = 0;
	while (theString[i])
		i++;
	return (i);
}
