/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 05:53:18 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/31 05:40:24 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	map_pos(t_game *game)
{
	game->player.map_x = floor(game->player.player_pos_x);
	game->player.map_y = floor(game->player.player_pos_y);
}

void	get_step_sideD(t_game *game)
{
	if (game->player.ray_dir_x < 0)
	{
		game->player.step_x = -1;
		game->player.side_dist_x = (game->player.player_pos_x - game->player.map_x) * game->player.d_dist_x;
	}
	else
	{
		game->player.step_x = 1;
		game->player.side_dist_x = (game->player.map_x + 1.0 - game->player.player_pos_x) * game->player.d_dist_x;
	}
	if (game->player.ray_dir_y < 0)
	{
		game->player.step_y = -1;
		game->player.side_dist_y = (game->player.player_pos_y - game->player.map_y) * game->player.d_dist_y;
	}
	else
	{
		game->player.step_y = 1;
		game->player.side_dist_y = (game->player.map_y + 1.0 - game->player.player_pos_y) * game->player.d_dist_y;
	}
}

void	get_the_ray(t_game *game)
{
	game->pixel = 2 * (game->pixel) / ((double)W_WIDTH) -1;
	game->player.ray_dir_x = game->player.dir_x + game->player.plane_x * game->pixel;
	game->player.ray_dir_y = game->player.dir_y + game->player.plane_y * game->pixel;
	map_pos(game);
	if (game->player.ray_dir_x == 0)
		game->player.d_dist_x = 1e30;
	else
		game->player.d_dist_x = fabs(1 / game->player.ray_dir_x);
	if (game->player.ray_dir_y == 0)
		game->player.d_dist_y = 1e30;
	else
		game->player.d_dist_y = fabs(1 / game->player.ray_dir_y);
	get_step_sideD(game);
}

void	apply_dda(t_game *game)
{
	while (game->player.hit == 0)
	{
		if (game->player.side_dist_x < game->player.side_dist_y)
		{
			game->player.side_dist_x += game->player.d_dist_x;
			game->player.map_x += game->player.step_x;
			game->player.wall_side = 0;
		}
		else
		{
			game->player.side_dist_y += game->player.d_dist_y;
			game->player.map_y += game->player.step_y;
			game->player.wall_side = 1;
		}
		if (game->map[game->player.map_y][game->player.map_x] == '1')
			game->player.hit = 1;
	}
}