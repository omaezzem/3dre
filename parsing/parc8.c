/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:30:32 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/21 15:14:28 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	find_player_in_line(char *line, int y, t_cub *cub)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == 'N' || line[x] == 'S'
			|| line[x] == 'E' || line[x] == 'W')
		{
			cub->player_pos.x = x;
			cub->player_pos.y = y;
			return (1);
		}
		x++;
	}
	return (0);
}

void	find_p(t_cub *cub)
{
	int	y;
	int	found;

	y = 0;
	found = 0;
	while (cub->map_lines[y])
	{
		if (find_player_in_line(cub->map_lines[y], y, cub))
		{
			found = 1;
			break ;
		}
		y++;
	}
	if (!found)
	{
		ft_putstr_fd("Error: Player not found in map\n", 2);
		return ;
	}
}

int	check_maps(char **map)
{
	int	i;

	i = 0;
	i = ft_strlen(map[0]);
	if (map[1][i] == '0')
		return (0);
	return (1);
}
