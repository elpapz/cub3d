/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_get_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:48:37 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/15 06:42:35 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	free_n_exit(t_game *game)
{
	if (!game)
		return ;
	if (game->north)
		free (game->north);
	if (game->south)
		free (game->south);
	if (game->east)
		free (game->east);
	if (game->west)
		free (game->west);
	if (game->line)
		free (game->line);
	if (game->map)
		free_array(game->map);
}
/*
void	print_array(char **str)
{
	int i = -1;
	while (str[++i])
		ft_putendl_fd(str[i], STDOUT_FILENO);
}
*/
void	player_start_coord(t_game *game, char **map)
{
	int	x;
	int	y;
	
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
			|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				game->start_coord_y = y;
				game->start_coord_x = x;
			}
		}
	}
}

void	check_inner_map(t_game *game, char **map)
{
	int	i;
	char **temp;

	i = 0;
	while (map[i])
		i++;
	temp = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (map[++i])
		temp[i] = ft_strdup(map[i]);
	player_start_coord(game, temp);
	//printf("x coord= %d\n y coord= %d\n", game->start_coord_x, game->start_coord_y);
	flood_fill(game, game->start_coord_x, game->start_coord_y, temp);
	//print_array(temp);
}

void	get_map(t_game *game, int fd)
{
	char	*temp;

	temp = NULL;
	while (game->line != NULL)
	{
		if (forbiden_or_empty(game->line) == false)
			exit_error(game, "your map is wrong!\n");
		if (!temp)
			temp = ft_strdup(game->line);
		else
			temp = ft_strjoin(temp, game->line);
		free (game->line);
		game->line = get_next_line(fd);
	}
	game->map = ft_split(temp, '\n');
	free (temp);
	if (!is_out_wall_closed(game->map) || check_num_players(game, game->map) != 1)
		exit_error (game, "out walls not closed\n");
	check_inner_map(game, game->map);
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
	get_map(game, fd);
	close (fd);
	return (true);
}