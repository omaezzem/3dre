/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 10:47:10 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/10 13:57:06 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
	t_cub cub;

	init_cub(&cub);
	if (!pars_av(ac, av))
	{
		fprintf(stderr, "Error\n Invalid arguments\n");
		return (EXIT_FAILURE);
	}
	if (!read_map(av[1], &cub))
	{
		fprintf(stderr, "Error\n Failed to read map\n");
		return (EXIT_FAILURE);
	}
	if (!pars_map(&cub))
	{
		fprintf(stderr, "Error\n Invalid map\n");
		return (EXIT_FAILURE);
	}
	change_space(&cub);
	cub.map_lines = ft_split(cub.map, '\n');
	if (!cub.map_lines)
	{
		fprintf(stderr, "Error\n Failed to split map\n");
		return (EXIT_FAILURE);
	}
	find_p(&cub);
	init_player_raycasting(&cub);
	cub.floor_color = 0x573D32;
	cub.ceiling_color = 0x000000;
	mlx_initcub(&cub);
	return (0);
}
