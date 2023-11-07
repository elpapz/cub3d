/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:37 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/07 02:35:28 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	move_up(t_game *game)
{
	game->player.player_pos_y += MOV * game->player.dir_y * 1;
	game->player.player_pos_x += MOV * game->player.dir_x * 1;
	if (game->map[(int)game->player.player_pos_y][(int)game->player.player_pos_x] != '0')
	{
		game->player.player_pos_y -= MOV * game->player.dir_y * 1;
		game->player.player_pos_x -= MOV * game->player.dir_x * 1;
	}
	else
		game_loop(game);
}

void	move_down(t_game *game)
{
	game->player.player_pos_y += MOV * game->player.dir_y * (-1);
	game->player.player_pos_x += MOV * game->player.dir_x * (-1);
	if (game->map[(int)game->player.player_pos_y][(int)game->player.player_pos_x] != '0')
	{
		game->player.player_pos_y -= MOV * game->player.dir_y * (-1);
		game->player.player_pos_x -= MOV * game->player.dir_x * (-1);
	}
	else
		game_loop(game);
}

void	move_left(t_game *game)
{
	game->player.player_pos_y += MOV * rotate_vec(game->player.dir_x, game->player.dir_y, 'y') * 1;
	game->player.player_pos_x += MOV * rotate_vec(game->player.dir_x, game->player.dir_y, 'x') * 1;
	if (game->map[(int)game->player.player_pos_y][(int)game->player.player_pos_x] != '0')
	{
		game->player.player_pos_y -= MOV * rotate_vec(game->player.dir_x, game->player.dir_y, 'y') * 1;
		game->player.player_pos_x -= MOV * rotate_vec(game->player.dir_x, game->player.dir_y, 'x') * 1;
	}
	else
		game_loop(game);
}

void	move_right(t_game *game)
{
	game->player.player_pos_y += MOV * rotate_vec(game->player.dir_x, game->player.dir_y, 'y') * (-1);
	game->player.player_pos_x += MOV * rotate_vec(game->player.dir_x, game->player.dir_y, 'x') * (-1);
	if (game->map[(int)game->player.player_pos_y][(int)game->player.player_pos_x] != '0')
	{
		game->player.player_pos_y -= MOV * rotate_vec(game->player.dir_x, game->player.dir_y, 'y') * (-1);
		game->player.player_pos_x -= MOV * rotate_vec(game->player.dir_x, game->player.dir_y, 'x') * (-1);
	}
	else
		game_loop(game);
}

int	move_player(int	key, t_game *game)
{
	if (key == ESC)
		finish_game(game);
	if (key == W)
		move_up(game);
	if (key == S)
		move_down(game);
	if (key == A)
		move_left(game);
	if (key == D)
		move_right(game);
	if (key == RIGHT)
		rotate_right(game);
	if (key == LEFT)
		rotate_left(game);
	return (0);
}