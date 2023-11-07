/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 01:54:43 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/07 02:46:01 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "./libft/libft.h"
# include "./minilibx/mlx.h"
# include <stdbool.h>
# include <math.h>

#define A 97
#define S 115
#define D 100
#define W 119

#define ESC 65307
#define RIGHT 65363
#define LEFT 65361

# define NORTH_IMG "./sprites/north_wall.xpm"
# define SOUTH_IMG "./sprites/south_wall.xpm"
# define EAST_IMG "./sprites/east_wall.xpm"
# define WEST_IMG "./sprites/west_wall.xpm"

#define W_HEIGHT 226
#define W_WIDTH 426
#define TILE_SIZE 64
#define PLANE 0.66

#define PI 3.14159265358979323846

#define MOV 0.2
#define ROT 0.1

typedef struct s_animation
{
	void	*noth_img;
	void	*south_img;
	void	*east_img;
	void	*west_img;
}			t_animation;


typedef struct s_player_view
{
	float		player_pos_x;
	float		player_pos_y;
	char		play_start_dir;
	double		plane_x;
	double		plane_y;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		ray_dir_x;
	double		ray_dir_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	double		d_dist_x;
	double		d_dist_y;
	int			hit;
	int			wall_side;
	int			start_draw;
	int			end_draw;
	double		wall_height;
	double		perp_wall_dist;
}				t_player_view;

typedef struct s_game
{
	t_animation	animation;
	void	*mlx;
	void	*mlx_window;
	char	**map;
	int		floor;
	int		ceiling;
	int		wall;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*line;
	int		pixel;
	t_player_view	player;
}			t_game;

void	check_input(int ac, char **av);
void	inicialize(t_game *game);
bool	get_color_n_textures(t_game *game, char *file);
int		exit_error(t_game *game, char *msg);
void	free_array(char **split);
void	is_valid_file(t_game *game, char *line);
bool	is_all_numbers(char **colors);
bool	line_empty(char *line);
int		exit_error(t_game *game, char *error_text);
void	get_texture(t_game *game, char *line, char c);
bool	split_colors(char **colors, char *line, size_t i);
bool	convert_rgb(t_game *game, char **colors, char c);
void	get_rgb(t_game *game, char *line, char c);
bool	forbiden_or_empty(char *line);
void	flood_fill(t_game *game, int x, int y, char **str);
bool	is_out_wall_closed(char **map);
bool	check_first_last_wall(char *str);
int		check_num_players(char **map);
bool	overall_parse_check(t_game *game, bool map);
bool	check_line(t_game *game, char *line);
bool	check_line_again(t_game *game, char *temp);
void	free_n_exit(t_game *game);
void	player_start_coord(t_game *game, char **map);
void	check_inner_map(t_game *game, char **map);
void	get_map(t_game *game, int fd);
bool	get_color_n_textures(t_game *game, char *file);
void	init_graphics(t_game *game);
int		render_backgroung(t_game *game);
void	apply_dda(t_game *game);
void	get_the_ray(t_game *game);
void	get_step_sideD(t_game *game);
void	map_pos(t_game *game);
void	get_wall_height(t_player_view *player);
void	get_player_direction(t_game *game, char c);
void	draw_column(t_game *game);
int		game_loop(t_game *game);
void	get_player_direction(t_game *game, char c);
int		move_player(int key, t_game *game);
int		finish_game(t_game *game);
double	rotate_vec(double x, double y, int flag);
void	rotate_right(t_game *game);
void	rotate_left(t_game *game);

#endif