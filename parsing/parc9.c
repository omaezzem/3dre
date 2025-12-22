/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:37:30 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/21 17:44:08 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	is_invalid_char(char c)
{
	return (c == ' ' || c == '\0');
}

static int	check_adjacent(t_cub *cub, int i, int j)
{
	if (i == 0 || j == 0 || !cub->map_lines[i + 1])
		return (0);
	if (j >= (int)strlen(cub->map_lines[i - 1])
		|| j >= (int)strlen(cub->map_lines[i + 1]))
		return (0);
	if (is_invalid_char(cub->map_lines[i][j - 1])
		|| is_invalid_char(cub->map_lines[i][j + 1])
		|| is_invalid_char(cub->map_lines[i - 1][j])
		|| is_invalid_char(cub->map_lines[i + 1][j]))
		return (0);
	return (1);
}

int	check_ziro(t_cub *cub)
{
	int	i;
	int	j;

	if (!cub || !cub->map_lines)
		return (0);
	i = 0;
	while (cub->map_lines[i])
	{
		j = 0;
		while (cub->map_lines[i][j])
		{
			if (cub->map_lines[i][j] == '0' || cub->map_lines[i][j] == 'N'
				|| cub->map_lines[i][j] == 'S' || cub->map_lines[i][j] == 'E'
				|| cub->map_lines[i][j] == 'W')
				if (!check_adjacent(cub, i, j))
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	new_lines_map(t_cub *cub)
{
	int	i;
	int	end;

	i = 0;
	while (cub->map[i] && cub->map[i] == '\n')
		i++;
	end = ft_strlen(cub->map) - 1;
	while (end > i && cub->map[end] == '\n')
		end--;
	while (i < end)
	{
		if (cub->map[i] == '\n' && cub->map[i + 1] == '\n')
		{
			printf("Error: New line inside map\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_map_lines(t_cub *cub)
{
	int	i;

	if (!cub || !cub->map_lines)
		return ;
	i = 0;
	while (cub->map_lines[i])
	{
		free(cub->map_lines[i]);
		i++;
	}
	free(cub->map_lines);
	cub->map_lines = NULL;
}
