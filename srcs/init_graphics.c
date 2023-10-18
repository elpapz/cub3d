/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 03:11:21 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/18 05:40:16 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	check_img(t_game *game)
{
	if (!game->animation.noth_img || !game->animation.east_img
	|| !game->animation.west_img || !game->animation.south_img)
		exit_error(game, "convert xmp to img just failed\n");
}

void	init_xpm_img(t_game *game)
{
	int	tile_size;

	tile_size = TILE_SIZE;
	game->animation.noth_img = mlx_xpm_file_to_image(game->mlx, NORTH_IMG, &tile_size, &tile_size);
	game->animation.south_img = mlx_xpm_file_to_image(game->mlx, SOUTH_IMG, &tile_size, &tile_size);
	game->animation.east_img = mlx_xpm_file_to_image(game->mlx, EAST_IMG, &tile_size, &tile_size);
	game->animation.west_img = mlx_xpm_file_to_image(game->mlx, WEST_IMG, &tile_size, &tile_size);
	check_img(game);
}

void	init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_window = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "cub3d");
	init_xpm_img(game);
	render_backgroung(game);
	mlx_loop(game->mlx);
	//printf("floor = %d\n", game->floor);
	//printf("ceiling = %d\n", game->ceiling);
}
