/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_get_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:48:37 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/14 03:26:11 by acanelas         ###   ########.fr       */
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
	//printf("is_valid flood %i\n", game->is_valid);
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
		//printf("is_valid get_map %i\n", game->is_valid);
		if (!forbiden_or_empty(game->line) && !game->is_valid)
			game->is_valid = 4;
		if (!temp)
			temp = ft_strdup(game->line);
		else
			temp = ft_strjoin_free(temp, game->line);
		free (game->line);
		game->line = get_next_line(fd);
	}
	game->map = ft_split(temp, '\n');
	free (temp);
	//printf("is_valid get_map %i\n", game->is_valid);
	if (!is_out_wall_closed(game->map) && !game->is_valid)
		game->is_valid = 5;
	//printf("is_valid get_map %i\n", game->is_valid);
	if (check_num_players(game->map) != 1 && !game->is_valid)
		game->is_valid = 6;
	//printf("is_valid get_map %i\n", game->is_valid);
	check_inner_map(game, game->map);
}

void	first_parse_check(t_game *game, bool map)
{
	printf("is_valid first parse: %i\n", game->is_valid);
	if (map == false)
		exit_game(game, "There's no actual map in your file\n");
	if (!game->is_valid && (game->ceiling == -1 || game->floor == -1))
		game->is_valid = 8;
	else if (!game->north || !game->south || !game->east || !game->west)
		game->is_valid = 8;
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
	first_parse_check(game, map);
	get_map(game, fd);
	overall_parse_check(game);
	//get_map(game, fd);
	close (fd);
	return (true);
}
