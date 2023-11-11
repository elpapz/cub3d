/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_n_textures2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 06:39:04 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/11 05:47:50 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

bool	check_line_again(t_game *game, char *temp)
{
	if (ft_strncmp(temp, "F", 1) == 0)
		get_rgb(game, temp, 'F');
	else if (ft_strncmp(temp, "C", 1) == 0)
		get_rgb(game, temp, 'C');
	else if (temp[0] == '0' || temp[0] == '1')
		return (false);
	else if (temp[0] != '\0')
	{
		free (temp);
		exit_game(game, "invalid map file\n");
	}
	return (true);
}

bool	check_line(t_game *game)
{
	char *temp;

	temp = ft_strtrim(game->line, " \t\n\v\f\r");
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
