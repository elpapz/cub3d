/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_n_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 06:31:34 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/15 06:35:05 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	get_texture(t_game *game, char *line, char c)
{
	int	i;

	i = 2;
	while (line[i] == ' ' || (line [i] >= 9 && line[i] <= 13))
		i++;
	is_valid_file(game, line + i);
	if (c == 'N' && !game->north)
		game->north = ft_strdup(line + i);
	else if (c == 'S' && !game->south)
		game->south = ft_strdup(line + i);
	else if (c == 'E' && !game->east)
		game->east = ft_strdup(line + i);
	else if (c == 'W' && !game->west)
		game->west = ft_strdup(line + i);
	else
	{
		free (line);
		exit_error(game, "error in get texture\n");
	}
}

bool	split_colors(char **colors, char *line, size_t i)
{
	int	start;
	int	word_count;

	word_count = 0;
	while (i < ft_strlen(line))
	{
		start = i;
		while (line[i] != ',' && line[i] != '\0')
			i++;
		if (line[i] == ',' || line[i] == '\0')
			colors[word_count++] = ft_substr(line, start, i - start);
		if (line[i] == '\0' || word_count > 3)
			break ;
		i++;
	}
	colors[word_count] = NULL;
	if (word_count != 3)
		return (false);
	return (true);
}

bool	convert_rgb(t_game *game, char **colors, char c)
{
	int i;
	int	*rgb;

	i = -1;
	rgb = malloc(sizeof(int) * 3);
	while (++i < 3)
		rgb[i] = ft_atoi(colors[i]);
	i = -1;
	while (++i < 3)
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free (rgb);
			return (false);
		}
	if (c == 'F' && game->floor == -1)
		game->floor = (0 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	if (c == 'C' && game->ceiling == -1)
		game->ceiling = (0 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	free (rgb);
	return (true);
}

void	get_rgb(t_game *game, char *line, char c)
{
	if (game->north == NULL || game->east == NULL || game->west == NULL || game->south == NULL)
	{
		free (line);
		exit_error(game, "Map elements are in the wrong order\n");
	}
	size_t	i;
	char **colors;

	i = 1;
	colors = malloc(sizeof(char *) * 3 + 1);
	while (line[i] == ' ' || (line [i] >= 9 && line[i] <= 13))
		i++;
	if (!split_colors(colors, line, i) || !is_all_numbers(colors) || !convert_rgb(game, colors, c))
	{
		free_array (colors);
		free (line);
		exit_error(game, "The RGB color code is wrong!\n");
	}
	free_array(colors);
}

bool	forbiden_or_empty(char *line)
{
	int	i;
	bool	is_empty;
	bool	is_valid_char;

	i = 0;
	is_empty = true;
	is_valid_char = true;
	while (line[i] && is_empty == true)
		if (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i++;
		else
			is_empty = false;
	i = 0;
	while (line[i] && is_empty == false && is_valid_char == true)
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			is_valid_char = false;
		}
	i++;
	}
	if (is_empty == true || is_valid_char == false)
		return (false);
	return (true);
}
