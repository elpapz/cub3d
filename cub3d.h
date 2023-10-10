/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 01:54:43 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/09 05:51:50 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "../libft/src/libft.h"
//# include "../minilibx/mlx.h"
# include <stdbool.h>

#define A 97
#define S 115
#define D 100
#define W 119

typedef struct s_game
{
	int	floor;
	int	ceiling;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*line;
}			t_game;


void	check_input(int ac, char **av);
void	inicialize(t_game *game);

#endif