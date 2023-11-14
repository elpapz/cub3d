/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_n_textures2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 06:39:04 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/14 03:28:42 by acanelas         ###   ########.fr       */
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
		game->is_valid = 2;
		//free (temp);
		//exit_game(game, "invalid map file\n");
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

bool	overall_parse_check(t_game *game)
{
	printf("is_valid overall %i\n", game->is_valid);
	//if (map == false)
		//exit_game(game, "There's no actual map in your file\n");
	if (game->is_valid == 8)
		exit_game(game, "Map data is in the wrong order or missing\n");
	else if (game->is_valid == 1)
		exit_game(game, "Unable to read input file\n");
	else if (game->is_valid == 2)
		exit_game(game, "Some trouble getting the texture files\n");
	else if (game->is_valid == 3)
		exit_game(game, "RGB code is wrong\n");
	else if (game->is_valid == 4)
		exit_game(game, "Forbidden char in your map\n");
	else if (game->is_valid == 5)
		exit_game(game, "Out walls not closed\n");
	else if (game->is_valid == 6)
		exit_game(game, "Your map must have 1 player, no more, no less\n");
	else if (game->is_valid == 7)
		exit_game(game, "Inner walls not closed\n");
	return (0);
}
