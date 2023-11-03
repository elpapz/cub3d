/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:40:55 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/03 04:17:08 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

int	main (int ac, char **av)
{
	t_game game;

	check_input(ac, av);
	inicialize(&game);
	if (!get_color_n_textures(&game, av[1]))
		exit_error(&game, "Map params are someway wrong\n");
	init_graphics(&game);
	game_loop(&game);
	mlx_loop(game.mlx);
	free_n_exit(&game);
}