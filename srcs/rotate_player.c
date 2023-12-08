/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 01:07:09 by acanelas          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/08 21:21:57 by acanelas         ###   ########.fr       */
=======
/*   Updated: 2023/12/08 20:06:50 by acanelas         ###   ########.fr       */
>>>>>>> 31723e3ad456320c47bdb1d76612299082134cf7
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	rotate_vec(double x, double y, int flag)
{
	double	new_x;
	double	new_y;

	new_x = x * cos(PI / 2) - y * sin(PI / 2);
	new_y = x * sin(PI / 2) + y * cos(PI / 2);
	if (flag == 'x')
		return (new_x);
	else
		return (new_y);
}

void	rotate_right(t_game *game)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x
		* cos(ROT) - game->player.dir_y * sin(ROT);
	game->player.dir_y = old_dir_x
		* sin(ROT) + game->player.dir_y * cos(ROT);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x
		* cos(ROT) - game->player.plane_y * sin(ROT);
	game->player.plane_y = old_plane_x
		* sin(ROT) + game->player.plane_y * cos(ROT);
	game_loop(game);
}

void	rotate_left(t_game *game)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x
		* cos(ROT) - game->player.dir_y * sin(-ROT);
	game->player.dir_y = old_dir_x
		* sin(-ROT) + game->player.dir_y * cos(-ROT);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x
		* cos(-ROT) - game->player.plane_y * sin(-ROT);
	game->player.plane_y = old_plane_x
		* sin(-ROT) + game->player.plane_y * cos(-ROT);
	game_loop(game);
}
