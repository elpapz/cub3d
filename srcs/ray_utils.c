/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 06:07:13 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/03 06:37:13 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_wall_height(t_player_view *player)
{
	if (player->wall_side == 0)
		player->perp_wall_dist = (player->side_dist_x - player->d_dist_x);
	else
		player->perp_wall_dist = (player->side_dist_y - player->d_dist_y);
	if (player->perp_wall_dist)
		player->wall_height = (int)(W_HEIGHT / player->perp_wall_dist);
	else
		player->wall_height = W_HEIGHT;
	printf("wall hight%f\n", player->wall_height);
	printf("perp_dist %f\n", player->perp_wall_dist);
	player->start_draw = -player->wall_height / 2 + W_HEIGHT / 2;
	if (player->start_draw < 0)
		player->start_draw = 0;
	//printf("start %d\n", player->start_draw);
	player->end_draw = player->wall_height / 2 + W_HEIGHT / 2;
	if (player->end_draw >= W_HEIGHT)
		player->end_draw = W_HEIGHT - 1;
	printf("end %d\n", player->end_draw);
	//printf("%f\n", player->plane_y);
	
}

void	draw_column(t_game *game)
{
	int	x;
	int	y;

	y = game->player.end_draw;
	x = game->pixel;
	printf("start %d\n", y);
	while (y < game->player.start_draw && y < W_HEIGHT)
	{
		mlx_pixel_put(game->mlx, game->mlx_window, x, y, game->floor);
		y++;
		printf("fodasse\n");
	}
}
