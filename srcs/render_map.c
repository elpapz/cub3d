/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 05:36:51 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/31 06:21:25 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

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
				mlx_pixel_put(game->mlx, game->mlx_window, x, y, game->ceiling);
		else
			while (++x < W_WIDTH)
				mlx_pixel_put(game->mlx, game->mlx_window, x, y, game->floor);
	}
	return (0);
}

void	game_loop(t_game *game)
{
	render_backgroung(game);
	while (game->pixel < W_WIDTH)
	{
		map_pos(game);
		get_the_ray(game);
		apply_dda(game);
		get_wall_height(game);

		
		game->pixel++;
	}
}