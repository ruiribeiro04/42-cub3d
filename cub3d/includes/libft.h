#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

/* Basic functions */
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	*ft_memset(void *s, int c, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
int		ft_printf(const char *str, ...);
char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);

#endif