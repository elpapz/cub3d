/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:45:27 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/11 08:15:35 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	inicialize(t_game *game)
{
	game->ceiling = -1;
	game->floor = -1;
	game->line = NULL;
	game->north = NULL;
	game->south = NULL;
	game->east = NULL;
	game->west = NULL;
}