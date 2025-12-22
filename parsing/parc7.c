/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:29:31 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/21 15:19:50 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	check_line_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0'
			&&line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	check_border_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	check_middle_lines(char **map_lines)
{
	int	i;
	int	j;

	j = 1;
	while (map_lines[j + 1])
	{
		i = 0;
		if (map_lines[j][i] != '1' && map_lines[j][i] != ' '
			&& map_lines[j][i] != '\t')
			return (0);
		if (!check_line_chars(map_lines[j]))
			return (0);
		i = strlen(map_lines[j]) - 1;
		if (map_lines[j][i] != '1' && map_lines[j][i] != ' '
			&& map_lines[j][i] != '\t')
			return (0);
		j++;
	}
	return (1);
}

int	pars_map(t_cub *cub)
{
	char	**map_lines;

	if (!cub->map)
		return (0);
	map_lines = ft_split(cub->map, '\n');
	if (!map_lines)
		return (0);
	if (!check_border_line(map_lines[0])
		|| !check_middle_lines(map_lines)
		|| !check_border_line(map_lines[ft_split_len(map_lines) - 1])
		|| !number_of_char(cub))
	{
		ft_free_split(map_lines);
		return (0);
	}
	ft_free_split(map_lines);
	return (1);
}

void	change_space(t_cub *cub)
{
	int	i;

	if (!cub->map)
		return ;
	i = 0;
	while (cub->map[i])
	{
		if (cub->map[i] == ' ' || cub->map[i] == '\t')
			cub->map[i] = '1';
		i++;
	}
}
