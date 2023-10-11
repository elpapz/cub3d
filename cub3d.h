/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 01:54:43 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/11 07:46:11 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "./libft/libft.h"
//# include "../minilibx/mlx.h"
# include <stdbool.h>

#define A 97
#define S 115
#define D 100
#define W 119

typedef struct s_game
{
	char	**map;
	int	floor;
	int	ceiling;
	char	play_start_dir;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*line;
}			t_game;


void	check_input(int ac, char **av);
void	inicialize(t_game *game);
bool	get_color_n_textures(t_game *game, char *file);
int	exit_error(t_game *game, char *msg);

#endif