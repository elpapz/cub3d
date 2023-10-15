/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 01:54:43 by acanelas          #+#    #+#             */
/*   Updated: 2023/10/15 06:48:00 by acanelas         ###   ########.fr       */
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
	int		floor;
	int		ceiling;
	int		start_coord_x;
	int		start_coord_y;
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
void	free_array(char **split);
void	is_valid_file(t_game *game, char *line);
bool	is_all_numbers(char **colors);
bool	line_empty(char *line);
int	exit_error(t_game *game, char *error_text);
void	get_texture(t_game *game, char *line, char c);
bool	split_colors(char **colors, char *line, size_t i);
bool	convert_rgb(t_game *game, char **colors, char c);
void	get_rgb(t_game *game, char *line, char c);
bool	forbiden_or_empty(char *line);
void	flood_fill(t_game *game, int x, int y, char **str);
bool	is_out_wall_closed(char **map);
bool	check_first_last_wall(char *str);
int	check_num_players(t_game *game, char **map);
bool	overall_parse_check(t_game *game, bool map);
bool	check_line(t_game *game, char *line);
bool	check_line_again(t_game *game, char *temp);
void	free_n_exit(t_game *game);
void	player_start_coord(t_game *game, char **map);
void	check_inner_map(t_game *game, char **map);
void	get_map(t_game *game, int fd);
bool	get_color_n_textures(t_game *game, char *file);

#endif