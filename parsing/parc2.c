/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:21:14 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/21 17:08:18 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	init_cub(t_cub *cub)
{
	cub->map = NULL;
	cub->texture = NULL;
	cub->NO = 0;
	cub->SO = 0;
	cub->WE = 0;
	cub->EA = 0;
	cub->F = 0;
	cub->C = 0;
	cub->north_texture = NULL;
	cub->south_texture = NULL;
	cub->west_texture = NULL;
	cub->east_texture = NULL;
	cub->map_lines = NULL;
	cub->_F = NULL;
	cub->_C = NULL;
}

int	pars_av(int ac, char **av)
{
	int	len;

	if (ac != 2)
		return (0);
	len = strlen(av[1]);
	if (len < 4)
		return (0);
	if (strcmp(av[1] + len - 4, ".cub") != 0)
		return (0);
	return (1);
}

void	init_texture(char *path, t_cub *cub)
{
	if (ft_strcmp(path, "NO") == 0)
		cub->NO += 1;
	else if (ft_strcmp(path, "SO") == 0)
		cub->SO += 1;
	else if (ft_strcmp(path, "WE") == 0)
		cub->WE += 1;
	else if (ft_strcmp(path, "EA") == 0)
		cub->EA += 1;
	else if (ft_strcmp(path, "F") == 0)
		cub->F += 1;
	else if (ft_strcmp(path, "C") == 0)
		cub->C += 1;
}

int	check_path(char *path)
{
	int	i;

	if (!path)
		return (0);
	i = 0;
	while (path[i])
		i++;
	if (i < 5)
		return (0);
	i--;
	while (i > 0 && (path[i] == ' ' || path[i] == '\t'
			|| path[i] == '\n' || path[i] == '\r'))
	{
		path[i] = '\0';
		i--;
	}
	if (i >= 3 && path[i] == 'm' && path[i - 1] == 'p'
		&& path[i - 2] == 'x' && path[i - 3] == '.')
		return (1);
	if (i >= 3 && path[i] == 'g' && path[i - 1] == 'n'
		&& path[i - 2] == 'p' && path[i - 3] == '.')
		return (1);
	return (0);
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}
