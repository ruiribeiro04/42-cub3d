/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:19:36 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
* @brief Reallocates the map array to accommodate one more line.
* 
* Creates a new array with space for one more line, copies the
* existing pointers, and frees the old array.
* 
* @param map Current map array (can be NULL).
* @param current_size Current number of rows in the map.
* @return char** New reallocated array, or NULL in case of error.
*/
char	**realloc_map(char **map, int current_size)
{
	char	**new_map;
	int		i;

	new_map = (char **)malloc(sizeof(char *) * (current_size + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < current_size)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[current_size + 1] = NULL;
	if (map)
		free(map);
	return (new_map);
}

/**
* @brief Removes the newline character from a line.
* 
* Replaces the first ‘\n’ found with ‘\0’.
* 
* @param line Line to be processed.
*/
void	strip_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	line[i] = '\0';
}

/**
* @brief Skips empty lines and returns the next non-empty line.
* 
* Reads from the file descriptor until it finds a line
* 	that is not just a newline.
* 
* @param fd File descriptor of the file.
* @return char* Next non-empty line, or NULL if EOF.
*/
char	*skip_empty_and_read(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

/**
* @brief Adds a line to the map array.
*
* Removes the newline from the line, reallocates the map, adds the line,
* and updates the maximum width of the map if necessary.
* Lines are stored as-is without padding to preserve original map structure.
*
* @param line Line to be added.
* @param map Pointer to the map array pointer.
* @param i Pointer to the current index (will be incremented).
* @param game Pointer to the game structure.
* @return int 1 on success, 0 on error.
*/
int	add_line_to_map(char *line, char ***map, int *i, t_game *game)
{
	int		line_len;

	strip_newline(line);
	line_len = ft_strlen(line);
	*map = realloc_map(*map, *i);
	if (!*map)
		return (0);
	(*map)[*i] = line;
	if (line_len > game->map_width)
		game->map_width = line_len;
	(*i)++;
	return (1);
}
