#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# define BUFFER_SIZE 1

char	*get_next_line(int fd);
char	*ft_gstrjoin(char const *s1, char const *s2);
char	*ft_gstrchr(const char *string, int searchedChar );

void	ft_gbzero(void *s, size_t n);
void	*ft_gcalloc(size_t elementCount, size_t elementSize);

size_t	ft_gstrlen(const char *theString);

#endif
