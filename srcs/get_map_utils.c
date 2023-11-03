/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 06:36:23 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/03 06:06:48 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	flood_fill(t_game *game, int x, int y, char **str)
{
	if (str[y][x] == ' ' || (str[y][x] >= 9 && str[y][x] <= 13))
	{
		free_array (str);
		exit_error(game, "flood fill error\n");
	}
	if (str[y][x] == '1')
		return ;
	str[y][x] = '1';
	flood_fill(game, x + 1, y, str);
	flood_fill(game, x - 1, y, str);
	flood_fill(game, x, y + 1, str);
	flood_fill(game, x, y - 1, str);
}

bool	is_out_wall_closed(char **map)
{
	int		last;
	int		i;
	char	**temp;

	last = 0;
	i = -1;
	while (map[last])
		last++;
	//printf("%d\n", last);
	temp = malloc(sizeof(char *) * (last + 1));
	while (map[++i])
		temp[i] = ft_strtrim(map[i], " \t\n\v\f\r");
	//printf("i = %d\n", i);
	temp[i] = NULL;
	//printf("temp[last -1] = %s\n", temp[last]);
	if (!check_first_last_wall(temp[0]) || !check_first_last_wall(temp[last - 1]))
		last = -1;
	i = -1;
	while (temp[++i] && last >= 0)
		if (temp[i][0] != '1' || temp[i][ft_strlen(temp[i]) - 1] != '1')
			last = -1;
	free_array(temp);
	if (last >= 0)
		return (true);
	return (false);
}

bool	check_first_last_wall(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != '1')
			return (false);
	return (true);
}

int	check_num_players(char **map)
{
	int	i;
	int	count_players;
	int j;

	i = -1;
	count_players = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == 'N' || map[i][j] == 'S'
			|| map[i][j] == 'W' || map[i][j] == 'E')
				{
					count_players += 1;
				}
	}
	return (count_players);
}

