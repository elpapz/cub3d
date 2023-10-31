/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:45:27 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/31 05:16:56 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	inicialize(t_game *game)
{
	game->player.play_start_dir = '\0';
	game->map = NULL;
	game->player.player_pos_x = 0;
	game->player.player_pos_y = 0;
	game->ceiling = -1;
	game->floor = -1;
	game->line = NULL;
	game->north = NULL;
	game->south = NULL;
	game->east = NULL;
	game->west = NULL;
	game->pixel = 0;
	game->player.hit = 0;
}