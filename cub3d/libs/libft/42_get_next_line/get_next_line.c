/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:43:43 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/08 23:01:42 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_buffer(int fd, char *stash)
{
	char	*buff;
	ssize_t	bytes_read;
	char	*temp;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr_gnl(stash, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(stash), free(buff), NULL);
		buff[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin_gnl(temp, buff);
		if (temp)
			free(temp);
	}
	free(buff);
	return (stash);
}

static char	*ft_extract_line(char *stash)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!stash || stash[0] == '\0')
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr_gnl(stash, 0, i);
	return (line);
}

static char	*ft_save_rest(char *stash)
{
	char	*rest;
	size_t	i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	rest = ft_strdup_gnl(stash + i);
	if (!rest)
		return (free(stash), NULL);
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_buffer(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	stash = ft_save_rest(stash);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		line_num;

	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	line_num = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", line_num++, line);
		free(line);
		line = NULL;
	}
	if (close(fd) == -1)
	{
		perror("Error closing file");
		return (1);
	}
	return (0);
}
*/
