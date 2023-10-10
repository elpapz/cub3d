/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_get_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:48:37 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/10 06:26:59 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_parse(t_game *cub3d)
{
	if (!cub3d)
		return ;
	if (cub3d->north)
		free (cub3d->north);
	if (cub3d->south)
		free (cub3d->south);
	if (cub3d->east)
		free (cub3d->east);
	if (cub3d->west)
		free (cub3d->west);
	if (cub3d->line)
		free (cub3d->line);
	//if (cub3d->colors)
		//free_split(cub3d->colors);
	//if (cub3d->temp_map)
		//free (cub3d->temp_map);
	//if (cub3d->map)
		//free_split(cub3d->map);
}

int	exit_error(t_game *game, char *msg)
{
	clean_parse(game);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	is_valid_file(t_game *game, char line)
{
	int	i;

	i = ft_strlen(line);
	if (!ft_strnstr(line, ".xpm", i))
		exit_error(game, "it should be a file ending with .xpm\n");
	int fd;
	
	fd = open(line, O_RDONLY);
	if (fd < 0)
		exit_error(game, "error opening XPM\n");
	close(fd);
}


void	get_texture(t_game *game, char *line, char c)
{
	int	i;

	i = 2;
	while (line[i] == ' ' || line [i] >= 9 && line[i] <= 13)
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
		exit_error(game, "error in get texture");
}

char	**split_colors(char *line, int i)
{
	int	start;
	int	word_count;
	char **colors;

	word_count = 0;
	start = i;
	colors = malloc(sizeof(char *) * 3);
	while (i < ft_strlen(line))
	{
		while (line[i] == ' ' || line[i] >= 9 && line[i] <= 13)
		{
			i++;
			start++;
		}
		if (line[i] == ',' || line[i] == '\0')
			colors[word_count++] = ft_substr(line, start, i - start);
		if (line[i] == '\0' || word_count > 3)
			break ;
		i++;
	}
	if (word_count > 3)
		return (NULL);
	return (colors);
}

void	get_rgb(t_game *game, char *line, char c)
{
	int	i;
	char **colors;

	i = 1;
	while (line[i] == ' ' || line [i] >= 9 && line[i] <= 13)
		i++;
	colors = split_colors(line, i);
	
	
}

void	check_line_again(t_game *game, char *temp, bool map)
{
	if (ft_strncmp(temp, "F", 1) == 0)
		get_rgb(game, temp, 'F');
	else if (ft_strncmp(temp, "C", 1) == 0)
		get_rgb(game, temp, 'C');
	else if (temp[0] == '0' || temp[0] == '1')
		map = true;
	else if (temp[0] != '\0')
		exit_error(game, "invalid map file\n");
}


void	check_line(t_game *game, char *line, bool map)
{
	//int	i;

	//i = 0;
	char *temp;	

	temp = ft_strtrim(line, " \t\n\v\f\r");
	//while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		//i++;
	if (ft_strncmp(temp, "NO", 2) == 0)
		get_texture(game, temp, 'N');
	else if (ft_strncmp(temp, "SO", 2) == 0)
		get_texture(game, temp, 'S');
	else if (ft_strncmp(temp, "EA", 2) == 0)
		get_texture(game, temp, 'E');
	else if (ft_strncmp(temp, "WE", 2) == 0)
		get_texture(game, temp, 'W');
	check_line_again(game, temp, map);
}

bool	get_map(t_game *game, char *map)
{
	int fd;
	bool	map;

	map = false;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return(false);
	game->line = get_next_line(fd);
	while (game->line != NULL)
	{
		check_line(game, game->line, map);
		if (map == true)
			break;
		free(game->line);
		game->line = get_next_line(fd);
	}
}