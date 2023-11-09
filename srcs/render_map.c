/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 05:36:51 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/08 23:51:59 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->map_img.addr + (y * game->map_img.line_len + x
		 * (game->map_img.bpp / 8));
	*(unsigned int *) dst = color;
}

void	create_map_image(t_game *game)
{
	//if (game->map_img.img)
		//mlx_destroy_image(game->mlx, game->map_img.img);
	game->map_img.img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	game->map_img.addr = mlx_get_data_addr(game->map_img.img, &game->map_img.bpp,
		&game->map_img.line_len, &game->map_img.endian);
}

int	render_backgroung(t_game *game)
{
	int y;
	int	x;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		if (y < W_HEIGHT / 2)
			while (++x < W_WIDTH)
			{
				//mlx_pixel_put(game->mlx, game->mlx_window, x, y, game->ceiling);
				my_mlx_pixel_put(game, x, y, game->ceiling);
			}
		else
			while (++x < W_WIDTH)
			{
				//mlx_pixel_put(game->mlx, game->mlx_window, x, y, game->floor);
				my_mlx_pixel_put(game, x, y, game->floor);
			}
	}
	return (0);
}

int	game_loop(t_game *game)
{
	create_map_image(game);
	render_backgroung(game);
	while (game->pixel < W_WIDTH)
	{
		map_pos(game);
		get_the_ray(game);
		get_step_sideD(game);
		apply_dda(game);
		get_wall_height(&game->player);
		draw_column(game);
		printf("pixel %i\n", game->pixel);
		game->pixel++;
	}
	//mlx_clear_window(game->mlx, game->mlx_window);
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->map_img.img, 0, 0);
	game->pixel = 0;
	return (0);
}