/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:45:27 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/16 22:09:30 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	inicialize(t_game *game)
{
	game->play_start_dir = '\0';
	game->map = NULL;
	game->start_coord_x = 0;
	game->start_coord_y = 0;
	game->ceiling = -1;
	game->floor = -1;
	game->line = NULL;
	game->north = NULL;
	game->south = NULL;
	game->east = NULL;
	game->west = NULL;
}