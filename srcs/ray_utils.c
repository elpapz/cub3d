/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 06:07:13 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/06 21:56:56 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	get_wall_height(t_player_view *player)
{
	if (player->wall_side == 0)
		player->perp_wall_dist = player->side_dist_x - player->d_dist_x;
	else
		player->perp_wall_dist = player->side_dist_y - player->d_dist_y;
	//if (player->perp_wall_dist)
		player->wall_height = (W_HEIGHT / player->perp_wall_dist);
	//else
		//player->wall_height = W_HEIGHT -1;
	printf("wall hight%f\n", player->wall_height);
	printf("perp_dist %f\n", player->perp_wall_dist);
	player->start_draw = (W_HEIGHT / 2) + (-player->wall_height / 2);
	if (player->start_draw >= W_HEIGHT)
		player->start_draw = W_HEIGHT - 1;
	//printf("start %d\n", player->start_draw);
	printf("start %d\n", player->start_draw);
	player->end_draw = (W_HEIGHT / 2) + (player->wall_height / 2);
	if (player->end_draw < 0)
		player->end_draw = 0;
	printf("end %d\n", player->end_draw);
	//printf("side_x %f\n", player->side_dist_x);
	//printf("side_y %f\n", player->side_dist_y);
	//printf("delta_x %f\n", player->d_dist_x);
	//printf("delta_y %f\n", player->d_dist_y);
	//printf("%f\n", player->plane_y);
}

void	draw_column(t_game *game)
{
	int	x;
	int	y;
	int	wall2 = (18 << 24 | 18 << 16 | 18 << 8 | 0);

	y = game->player.start_draw;
	x = game->pixel;
	while (y < game->player.end_draw && y < W_HEIGHT)
	{
		if (game->player.wall_side)
			mlx_pixel_put(game->mlx, game->mlx_window, x, y, game->wall);
		else
			mlx_pixel_put(game->mlx, game->mlx_window, x, y, wall2);
	y++;
		//printf("fodasse\n");
	}
	game->player.hit = 0;
}
