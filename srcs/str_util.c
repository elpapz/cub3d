/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 06:22:00 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/10 23:51:03 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	free_array(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	//free(split[i]);
	free(split);
}

void	is_valid_file(t_game *game, char *line)
{
	int	i;

	i = ft_strlen(line);
	if (!ft_strnstr(line, ".xpm", i))
		exit_error(game, "it should be a file ending with .xpm\n");
	int fd;

	fd = open(line, O_RDONLY);
	if (fd < 0)
		exit_error(game, "error opening XPM\n");
	close(fd);
}

bool	is_all_numbers(char **colors)
{
	int	i;
	int	j;

	i = 0;
	while (colors[i])
	{
		j = 0;
		while (colors[i][j])
			if (!ft_isdigit(colors[i][j]))
				return (false);
			else
				j++;
		i++;
	}
	return (true);
}

bool	line_empty(char *line)
{
	int	i;
	bool	is_empty;

	i = -1;
	is_empty = true;
	while (line[++i] && is_empty == true)
		if (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i++;
		else
			is_empty = false;

	return (true);
}

int	exit_error(t_game *game, char *error_text)
{
	free_n_exit(game);
	ft_putendl_fd("Ops, the game crashed", STDERR_FILENO);
	ft_putstr_fd(error_text, STDERR_FILENO);
	exit (EXIT_FAILURE);
}
