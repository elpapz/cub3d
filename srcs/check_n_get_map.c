/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_get_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:48:37 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/11 05:48:30 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

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
				game->player.player_pos_y = y + 0.5;
				game->player.player_pos_x = x + 0.5;
				game->map[y][x] = '0';
				game->player.play_start_dir = map[y][x];
				get_player_direction(game, game->player.play_start_dir);
			}
		}
	}
	//printf("player_dir = %c\n", game->play_start_dir);
	//printf("player_dir = %f\n", game->start_coord_y);
	//printf("player_dir = %f\n", game->start_coord_x);
}

void	check_inner_map(t_game *game, char **map)
{
	int	i;
	char **temp;

	i = 0;
	while (map[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (map[++i])
		temp[i] = ft_strdup(map[i]);
	temp[i] = NULL;
	player_start_coord(game, temp);
	//printf("x coord= %d\n y coord= %d\n", game->start_coord_x, game->start_coord_y);
	flood_fill(game, game->player.player_pos_x, game->player.player_pos_y, temp);
	free_array(temp);
	//print_array(temp);
}

void	get_map(t_game *game, int fd)
{
	char	*temp;

	temp = NULL;
	while (game->line != NULL)
	{
		if (forbiden_or_empty(game->line) == false)
			exit_game(game, "Your map is wrong!\n");
		if (!temp)
			temp = ft_strdup(game->line);
		else
			temp = ft_strjoin_free(temp, game->line);
		free (game->line);
		game->line = get_next_line(fd);
	}
	game->map = ft_split(temp, '\n');
	free (temp);
	if (!is_out_wall_closed(game->map) || check_num_players(game->map) != 1)
		exit_game (game, "Out walls not closed\n");
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
		if (!check_line(game))
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
