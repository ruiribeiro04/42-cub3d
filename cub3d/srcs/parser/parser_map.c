/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:19:39 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser_map.c
 * @brief Read the map grid from the open .cub file descriptor.
 */

#include "cub3d.h"

/**
* @brief Processes the first line of the map.
* 
* Initializes the map array and adds the first line
* that was read during the parsing of the elements.
* 
* @param first_line First line of the map.
* @param map Pointer to the map array pointer.
* @param i Pointer to the index (will be initialized to 0).
* @param game Pointer to the game structure.
* @return char* The processed line, or NULL in case of error.
*/
static char	*process_first_line(char *first_line, char ***map,
	int *i, t_game *game)
{
	char	*line;

	line = first_line;
	*map = NULL;
	*i = 0;
	if (line)
	{
		strip_newline(line);
		*map = realloc_map(*map, *i);
		if (!*map)
		{
			free(line);
			return (NULL);
		}
		(*map)[*i] = line;
		if ((int)ft_strlen(line) > game->map_width)
			game->map_width = ft_strlen(line);
		(*i)++;
	}
	return (line);
}

/**
* @brief Processes the remaining lines of the map.
* 
* Reads and adds all lines of the map until it finds
* an empty line or the end of the file.
* 
* @param fd File descriptor of the file.
* @param map Pointer to the pointer of the map array.
* @param i Pointer to the current index.
* @param game Pointer to the game structure.
* @return char* Last line read (can be NULL or an empty line).
*/
static char	*process_map_lines(int fd, char ***map, int *i, t_game *game)
{
	char	*line;

	line = skip_empty_and_read(fd);
	while (line && line[0] != '\n')
	{
		if (!add_line_to_map(line, map, i, game))
		{
			free(line);
			return (NULL);
		}
		line = skip_empty_and_read(fd);
	}
	return (line);
}

/**
* @brief Performs complete parsing of the map grid.
* 
* Main function that coordinates the parsing of all lines
* of the map, starting with the first line already read and continuing
* to the end of the map.
* 
* @param fd File descriptor of the open file.
* @param game Pointer to the game structure.
* @param first_line First line of the map (already read).
* @return char** Two-dimensional array representing the map, or NULL on error.
*/
char	**ft_parse_map_grid(int fd, t_game *game, char *first_line)
{
	char	*line;
	char	**map;
	int		i;

	if (!process_first_line(first_line, &map, &i, game))
		return (NULL);
	line = process_map_lines(fd, &map, &i, game);
	if (line)
		free(line);
	game->map_height = i;
	return (map);
}
