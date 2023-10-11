/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_get_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:48:37 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/11 09:43:29 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	free_array(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

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
	//ft_putstr_fd("\n", STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	is_valid_file(t_game *game, char *line)
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

bool	is_all_numbers(char **colors)
{
	int	i;
	int	j;

	i = 0;
	while (colors[i])
	{
		j = 0;
		while (colors[i][j])
			if (!ft_isdigit(colors[i][j]))
				return (false);
			else
				j++;
		i++;
	}
	return (true);
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

bool	check_line_again(t_game *game, char *temp)
{
	if (ft_strncmp(temp, "F", 1) == 0)
	{
		//printf ("fodasse3\n");
		get_rgb(game, temp, 'F');
		//printf ("fodasse4\n");
	}
	else if (ft_strncmp(temp, "C", 1) == 0)
	{
		//printf ("fodasse1\n");
		get_rgb(game, temp, 'C');
		//printf ("fodasse2\n");
	}
	else if (temp[0] == '0' || temp[0] == '1')
		return (false);
	else if (temp[0] != '\0')
	{
		free (temp);
		exit_error(game, "invalid map file\n");
	}
	return (true);
}


bool	check_line(t_game *game, char *line)
{
	char *temp;

	temp = ft_strtrim(line, " \t\n\v\f\r");
	//printf ("%s\n", temp);
	if (ft_strncmp(temp, "NO", 2) == 0)
		get_texture(game, temp, 'N');
	else if (ft_strncmp(temp, "SO", 2) == 0)
		get_texture(game, temp, 'S');
	else if (ft_strncmp(temp, "EA", 2) == 0)
		get_texture(game, temp, 'E');
	else if (ft_strncmp(temp, "WE", 2) == 0)
		get_texture(game, temp, 'W');
	else
		if (!check_line_again(game, temp))
		{
			free (temp);
			return (false);
		}
	free (temp);
	return (true);
}

bool	overall_parse_check(t_game *game, bool map)
{
	if (game->north && game->south && game->east && game->west
		&& game->floor != -1 && game->ceiling != -1 && map == true)
		return (true);
	else
		return (false);
}

bool	line_empty(char *line)
{
	int	i;
	bool	is_empty;

	i = -1;
	is_empty = true;
	while (line[++i] && is_empty == true)
		if (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i++;
		else
			is_empty = false;

	return (true);
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
	//printf("%s", line);
	//printf("is valid = %d\n", is_valid_char);
	while (line[i] && is_empty == false && is_valid_char == true)
	{
		//printf("%s", line);
		//printf("is valid = %d\n", is_valid_char);
		//printf("char = %c\n", line[i]);
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			is_valid_char = false;
		}
	i++;
	}
	//printf("is empty = %d\nis valid = %d\n", is_empty, is_valid_char);
	if (is_empty == true || is_valid_char == false)
		return (false);
	return (true);
}

int	check_num_players(t_game *game, char *file)
{
	int	i;
	int	count_players = 0;

	count_players = 0;
	i = 0;
	while (file[i])
	{
		if (file[i] == 'N' || file[i] == 'S'
		|| file[i] == 'W' || file[i] == 'E')
			{
				count_players += 1;
				game->play_start_dir = file[i];
			}
	i++;
	}
	return (count_players);
}

bool	is_out_wall_closed(char *line)
{
	size_t	last;
	int	i;
	char *temp;

	i = 0;
	temp = ft_strtrim(line, " \t\n\v\f\r");
	last = ft_strlen(temp) - 1;
		if (temp[0] == '1' && temp[last] == '1')
		{
			free (temp);
			return (true);
		}
		else
			free (temp);
	return (false);

}

void	get_map(t_game *game, int fd)
{
	int	i;
	char	*temp;

	temp = NULL;
	i = -1;
	while (game->line)
	{
		//printf("%s", game->line);
		if (forbiden_or_empty(game->line) == false)
			exit_error(game, "forbiden char/empty line\n");
		//printf("fodasse\n");
		if (is_out_wall_closed(game->line) == false)
			exit_error(game, "outside walls are unclosed");
		//printf("fodasse1\n");
		if (!temp)
			temp = ft_strdup(game->line);
		else
			temp = ft_strjoin(temp, game->line);
		//printf("fodasse2\n");
		free (game->line);
		game->line = get_next_line(fd);
	}
	//printf("%s\n", temp);
	//printf("fodasse2\n");
	if (check_num_players(game, temp) != 1)
		exit_error (game, "more than 1 player spawning\n");
	printf("%s", temp);
	game->map = ft_split(temp, '\n');
}

bool	get_color_n_textures(t_game *game, char *file)
{
	int fd;
	bool	map;

	map = false;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	game->line = get_next_line(fd);
	while (game->line)
	{
		if (!check_line(game, game->line))
			map = true;
		if (map == true)
			break ;
		free(game->line);
		game->line = get_next_line(fd);
	}
	if (overall_parse_check(game, map) == false)
		return (false);
	//close (fd);
	get_map(game, fd);
	close (fd);
	return (true);
}