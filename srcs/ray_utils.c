/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 06:07:13 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/14 20:06:31 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_pixel(t_animation *img, int x, int y)
{
	return (*(unsigned int *)((img->addr
			+ (y * img->line_len) + (x * (img->bpp / 8)))));
}

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
	//printf("wall hight%f\n", player->wall_height);
	//printf("perp_dist %f\n", player->perp_wall_dist);
	player->start_draw = (W_HEIGHT / 2) + (-player->wall_height / 2);
	if (player->start_draw < 0)
		player->start_draw = 0;
	//printf("start %d\n", player->start_draw);
	//printf("start %d\n", player->start_draw);
	player->end_draw = (W_HEIGHT / 2) + (player->wall_height / 2);
	if (player->end_draw >= W_HEIGHT)
		player->end_draw = W_HEIGHT -1;
	//printf("a tua mae\n");
	//printf("end %d\n", player->end_draw);
	//printf("a tua mae");
	//printf("side_x %f\n", player->side_dist_x);
	//printf("side_y %f\n", player->side_dist_y);
	//printf("delta_x %f\n", player->d_dist_x);
	//printf("delta_y %f\n", player->d_dist_y);
	//printf("%f\n", player->plane_y);
}

double	tex_pos(t_game *game, double y)
{
	double	pos;

	pos = (game->player.start_draw - W_HEIGHT
			/ 2 + game->player.wall_height / 2) * y;
	return (pos);
}

double	tex_step_y(t_game *game)
{
	double	y;

	y = 1.0 * TILE_SIZE / game->player.wall_height;
	return (y);
}

void	draw_column(t_game *game)
{
	int		x;
	int		y;
	double	step;
	double	pos;

	step = tex_step_y(game);
	pos = tex_pos(game, step);
	y = game->player.start_draw;
	x = game->pixel;
	printf("tex_x %i\n", game->player.t_x);
	//printf("pos %f\nstep %f\n", pos, step);
	while (y < game->player.end_draw)
	{
		game->player.t_y = (int)pos & (TILE_SIZE - 1);
		//printf("text_y %i\n", game->player.t_y);
		//printf("text_x %i\ntext_y %i\n", game->player.t_x, game->player.t_y);
		//printf("text_x %i\ntext_y %i\n", game->player.t_x, game->player.t_y);
		pos += step;
		game->color = get_pixel(&game->sprite_img,
				game->player.t_x, game->player.t_y);
		my_mlx_pixel_put(game, x, y, game->color);
		y++;
	}
	game->player.hit = 0;
}
