/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 10:47:10 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/22 16:17:51 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	init_map(t_cub *cub, char *file)
{
	if (!read_map(file, cub))
		return (0);
	if (!new_lines_map(cub))
		return (0);
	if (!handle_colors_str(cub->_F) || !handle_colors_str(cub->_C))
		return (0);
	if (!pars_map(cub))
		return (0);
	change_space(cub);
	if (cub->map_lines)
	{
		ft_free_split(cub->map_lines);
		cub->map_lines = NULL;
	}
	cub->map_lines = ft_split(cub->map, '\n');
	if (!cub->map_lines)
		return (0);
	find_p(cub);
	if (!check_maps(cub->map_lines))
		return (0);
	if (!check_ziro(cub))
		return (0);
	pad_map(cub->map_lines);
	return (1);
}

static char	*append_line(char *map, char *line)
{
	char	*tmp;
	char	*new_map;

	if (!map || !line)
		return (NULL);
	tmp = map;
	new_map = ft_strjoin(tmp, line);
	free(tmp);
	return (new_map);
}

static char	*append_newline(char *map)
{
	char	*tmp;
	char	*new_map;

	if (!map)
		return (NULL);
	tmp = map;
	new_map = ft_strjoin(tmp, "\n");
	free(tmp);
	return (new_map);
}

static int	build_map_string(t_cub *cub)
{
	int		i;

	if (!cub)
		return (0);
	free(cub->map);
	cub->map = ft_strdup("");
	if (!cub->map)
		return (0);
	i = 0;
	while (cub->map_lines[i])
	{
		cub->map = append_line(cub->map, cub->map_lines[i]);
		if (!cub->map)
			return (0);
		cub->map = append_newline(cub->map);
		if (!cub->map)
			return (0);
		i++;
	}
	return (1);
}

void f(){system("leaks cub3D");}

int	main(int ac, char **av)
{
	t_cub	cub;
	atexit(f);
	init_cub(&cub);
	if (!pars_av(ac, av))
	{
		cleanup(&cub);
		return (printf("Error: Invalid arguments\n"), EXIT_FAILURE);
	}
	if (!init_map(&cub, av[1]))
	{
		cleanup(&cub);
		return (printf("Error: Failed to init map\n"), EXIT_FAILURE);
	}
	build_map_string(&cub);
	cub.floor_color = 0x573D32;
	cub.ceil_color = 0x87CEEB;
	init_player_raycasting(&cub);
	mlx_initcub(&cub);
	cleanup(&cub);
	return (0);
}
