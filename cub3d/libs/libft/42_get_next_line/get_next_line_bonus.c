/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:21:45 by ruiferna          #+#    #+#             */
/*   Updated: 2025/06/08 23:01:42 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read_buffer(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_extract_line(stash[fd]);
	stash[fd] = ft_save_rest(stash[fd]);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int		*fds;
	char	*line;
	int		num_files;
	int		active_files;
	int		i;

	if (argc < 2)
	{
		printf("Usage: %s <file1> [file2] [file3] ...\n", argv[0]);
		return (1);
	}
	num_files = argc - 1;
	fds = malloc(sizeof(int) * num_files);
	if (!fds)
		return (perror("Error allocating memory for fds"), 1);
	i = 0;
	while (i < num_files)
	{
		fds[i] = open(argv[i + 1], O_RDONLY);
		if (fds[i] == -1)
		{
			perror("Error opening file");
			while (--i >= 0)
				close(fds[i]);
			free(fds);
			return (1);
		}
		i++;
	}
	active_files = num_files;
	while (active_files > 0)
	{
		i = 0;
		while (i < num_files)
		{
			if (fds[i] != -1)
			{
				line = get_next_line(fds[i]);
				if (line != NULL)
				{
					printf("FD %d: %s", fds[i], line);
					free(line);
				}
				else
				{
					if (close(fds[i]) == -1)
						perror("Error closing file");
					fds[i] = -1;
					active_files--;
				}
			}
			i++;
		}
	}
	free(fds);
	return (0);
}
*/
