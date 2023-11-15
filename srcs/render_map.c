/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 05:36:51 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/15 06:32:17 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->map_img.addr + (y * game->map_img.line_len + x
			* (game->map_img.bpp / 8));
	*(unsigned int *) dst = color;
}

void	create_map_image(t_game *game)
{
	if (game->map_img.img)
		mlx_destroy_image(game->mlx, game->map_img.img);
	game->map_img.img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	game->map_img.addr = mlx_get_data_addr(game->map_img.img,
			&game->map_img.bpp,
			&game->map_img.line_len, &game->map_img.endian);
}

int	render_backgroung(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		if (y < W_HEIGHT / 2)
			while (++x < W_WIDTH)
				my_mlx_pixel_put(game, x, y, game->ceiling);
		else
			while (++x < W_WIDTH)
				my_mlx_pixel_put(game, x, y, game->floor);
	}
	return (0);
}

double	get_wall_side(t_player_view *player)
{
	double	wall;

	if (!player->wall_side)
	{
		wall = player->player_pos_y
			+ player->perp_wall_dist * player->ray_dir_y;
	}
	else
	{
		wall = player->player_pos_x
			+ player->perp_wall_dist * player->ray_dir_x;
	}
	wall -= floor(wall);
	return (wall);
}

int	final_x_text(t_player_view *player)
{
	int	texture;

	if (!player->wall_side && player->ray_dir_y < 0)
		texture = player->t_x - TILE_SIZE - 1;
	if (player->wall_side && player->ray_dir_x > 0)
		texture = player->t_x - TILE_SIZE - 1;
	else
		texture = player->t_x;
	return (texture);
}

void	get_x_text(t_player_view *player)
{
	double	wall;

	wall = get_wall_side(player);
	player->t_x = (int)(wall * (double)(TILE_SIZE));
	if (!player->wall_side && player->ray_dir_x < 0)
		player->t_x = TILE_SIZE - player->t_x;
	else if (player->wall_side && player->ray_dir_y > 0)
		player->t_x = TILE_SIZE - player->t_x;
	//player->t_x = final_x_text(player);
}

void	save_sprite(t_game *game)
{
	if (!game->player.wall_side)
	{
		if (game->player.player_pos_x < game->player.map_x)
			game->sprite_img = game->east_img;
		else
			game->sprite_img = game->west_img;
	}
	else
	{
		if (game->player.player_pos_y > game->player.map_y)
			game->sprite_img = game->noth_img;
		else
			game->sprite_img = game->south_img;
	}
	get_x_text(&game->player);
}

int	game_loop(t_game *game)
{
	create_map_image(game);
	render_backgroung(game);
	while (game->pixel <= W_WIDTH)
	{
		map_pos(game);
		get_the_ray(game);
		get_step_sided(game);
		apply_dda(game);
		get_wall_height(&game->player);
		save_sprite(game);
		draw_column(game);
		//printf("pixel %i\n", game->pixel);
		game->pixel++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_window,
		game->map_img.img, 0, 0);
	game->pixel = 0;
	return (0);
}
