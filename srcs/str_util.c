/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 06:22:00 by acanelas          #+#    #+#             */
/*   Updated: 2023/11/11 05:46:35 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

bool	is_valid_file(char *line)
{
	int	i;

	i = ft_strlen(line);
	if (!ft_strnstr(line, ".xpm", i))
	{
		//free (line);
		//exit_game(game, "it should be a file ending with .xpm\n");
		return (false);
	}
	int fd;

	fd = open(line, O_RDONLY);
	if (fd < 0)
	{
		//printf("fuck");
		close (fd);
		return (false);
		//free (line);
		//exit_game(game, "error opening XPM\n");
	}
	close(fd);
	return (true);
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
