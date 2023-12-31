/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 03:11:21 by acanelas          #+#    #+#             */
/*   Updated: 2023/12/08 21:51:43 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_img(t_game *game)
{
	if (!game->noth_img.img || !game->east_img.img
		|| !game->west_img.img || !game->south_img.img)
	{
		destroy_img(game);
		mlx_destroy_window(game->mlx, game->mlx_window);
		mlx_destroy_display(game->mlx);
		free (game->mlx);
		free_n_exit(game);
		ft_putendl_fd("convert xmp to img just failed", STDOUT_FILENO);
		exit(0);
	}
}

void	init_addr(t_game *game)
{
	game->noth_img.addr = mlx_get_data_addr(game->noth_img.img,
			&game->noth_img.bpp, &game->noth_img.line_len,
			&game->noth_img.endian);
	game->east_img.addr = mlx_get_data_addr(game->east_img.img,
			&game->east_img.bpp, &game->east_img.line_len,
			&game->east_img.endian);
	game->west_img.addr = mlx_get_data_addr(game->west_img.img,
			&game->west_img.bpp, &game->west_img.line_len,
			&game->west_img.endian);
	game->south_img.addr = mlx_get_data_addr(game->south_img.img,
			&game->south_img.bpp, &game->south_img.line_len,
			&game->south_img.endian);
}

void	check_size_xpm(int tile_x, int tile_y, t_game *game)
{
	if (tile_x != TILE_SIZE || tile_y != TILE_SIZE)
	{
		destroy_img(game);
		mlx_destroy_window(game->mlx, game->mlx_window);
		mlx_destroy_display(game->mlx);
		free (game->mlx);
		free_n_exit(game);
		ft_putendl_fd("Invalid xpm size", STDOUT_FILENO);
		exit(0);
	}
}

void	init_xpm_img(t_game *game)
{
	int	tile_size_x;
	int	tile_size_y;

	tile_size_x = 0;
	tile_size_y = 0;
	game->noth_img.img = mlx_xpm_file_to_image
		(game->mlx, game->north, &tile_size_x, &tile_size_y);
	check_size_xpm(tile_size_x, tile_size_y, game);
	game->south_img.img = mlx_xpm_file_to_image
		(game->mlx, game->south, &tile_size_x, &tile_size_y);
	check_size_xpm(tile_size_x, tile_size_y, game);
	game->east_img.img = mlx_xpm_file_to_image
		(game->mlx, game->east, &tile_size_x, &tile_size_y);
	check_size_xpm(tile_size_x, tile_size_y, game);
	game->west_img.img = mlx_xpm_file_to_image
		(game->mlx, game->west, &tile_size_x, &tile_size_y);
	check_size_xpm(tile_size_x, tile_size_y, game);
	check_img(game);
	init_addr(game);
}

void	init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_window = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "cub3d");
	init_xpm_img(game);
}
