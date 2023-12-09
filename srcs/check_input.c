/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 01:56:23 by acanelas          #+#    #+#             */
/*   Updated: 2023/12/09 04:41:23 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_input(int ac, char **av)
{
	if (ac != 2)
	{
		ft_printf("Wrong number of arguments\n");
		exit (EXIT_SUCCESS);
	}
	auto int i = ft_strlen(av[1]);
	if (!ft_strnstr(av[1], ".cub", i))
	{
		ft_printf("Wrong map extension! Try to write '.cub' at the end\n");
		exit (EXIT_SUCCESS);
	}
	if (av[1][i - 5] == '/' || av[1][i - 5] == ' ')
	{
		ft_printf("Right extension but no map name\n");
		exit (EXIT_SUCCESS);
	}
}
