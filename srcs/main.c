/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:40:55 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/07 00:37:54 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

int	finish_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_window);
	mlx_destroy_display(game->mlx);
	free (game->mlx);
	free_n_exit(game);
	ft_putendl_fd("Hope to see you back soon :)", STDOUT_FILENO);
	exit (0);
}


int	main (int ac, char **av)
{
	t_game game;

	check_input(ac, av);
	inicialize(&game);
	if (!get_color_n_textures(&game, av[1]))
		exit_error(&game, "Map params are someway wrong\n");
	init_graphics(&game);
	game_loop(&game);
	mlx_hook(game.mlx_window, 2, 1L << 0, move_player, &game);
	mlx_hook(game.mlx_window, 17, 1L << 17, finish_game, &game);
	mlx_loop(game.mlx);
	free_n_exit(&game);
}