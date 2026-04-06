#include "cub3d.h"

/**
* @brief Frees the memory of a string array.
* 
* Auxiliary function to free arrays created by ft_split.
* 
* @param values Array of strings to be freed.
*/
static void	ft_free_split(char **values)
{
	int	i;

	i = 0;
	while (values[i])
	{
		free(values[i]);
		i++;
	}
	free(values);
}

/**
* @brief Extracts the RGB values from a configuration line.
* 
* Splits the line and converts the values to integers,
* validating that they are in the range [0, 255].
* 
* @param line Line containing the RGB values (format: “F/C R G B”).
* @param r Pointer to store the red value.
* @param g Pointer to store the green value.
* @param b Pointer to store the blue value.
* @return int 0 on success, 1 on error.
*/
/**
* @brief Validates if a string represents a valid number.
*
* @param str String to validate.
* @return int 1 if valid number, 0 otherwise.
*/
static int	is_valid_number(char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	ft_parse_rgb_values(char *line, int *r, int *g, int *b)
{
	char	*str;
	char	**values;
	int		result;
	char	*tmp;
	int		i;

	str = &line[2];
	tmp = str;
	while (*tmp)
	{
		if (*tmp == ',')
			*tmp = ' ';
		tmp++;
	}
	values = ft_split(str, ' ');
	if (!values)
		return (1);
	result = 0;
	if (!values[0] || !values[1] || !values[2] || values[3])
		result = 1;
	// Strip newlines from values
	i = 0;
	while (!result && i < 3)
	{
		tmp = values[i];
		while (tmp && *tmp && *tmp != '\n')
			tmp++;
		if (*tmp == '\n')
			*tmp = '\0';
		i++;
	}
	if (!result && (!is_valid_number(values[0]) || !is_valid_number(values[1])
			|| !is_valid_number(values[2])))
		result = 1;
	if (!result)
	{
		*r = ft_atoi(values[0]);
		*g = ft_atoi(values[1]);
		*b = ft_atoi(values[2]);
		if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
			result = 1;
	}
	ft_free_split(values);
	return (result);
}

/**
* @brief Parses a color line (floor or ceiling).
* 
* Identifies whether it is floor color (F) or ceiling color (C),
* 	extracts the RGB values,
* combines them into a single 32-bit integer,
* 	and stores them in the game structure.
* Also checks for duplicate colors.
* 
* @param line Color configuration line.
* @param game Pointer to the game structure.
* @return int 1 on success, -1 on error.
*/
int	ft_parse_color(char *line, t_game *game)
{
	int	r;
	int	g;
	int	b;
	int	color;

	if (ft_parse_rgb_values(line, &r, &g, &b))
		return (ft_putstr_fd("Error: Invalid RGB color format\n", 2), 1);
	color = (r << 16) | (g << 8) | b;
	if (!ft_strncmp(line, "F ", 2))
	{
		if (game->floor_color != -1)
			return (ft_putstr_fd("Error: Duplicate floor color\n", 2), 1);
		game->floor_color = color;
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		if (game->ceiling_color != -1)
			return (ft_putstr_fd("Error: Duplicate ceiling color\n", 2), 1);
		game->ceiling_color = color;
	}
	return (0);
}
