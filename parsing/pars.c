/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:36:42 by omaezzem          #+#    #+#             */
/*   Updated: 2025/12/21 17:41:16 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	get_max_len(char **lines)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (lines[i])
	{
		len = strlen(lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	*pad_line(char *line, int max_len)
{
	int		len;
	char	*new_line;
	int		i;

	len = strlen(line);
	new_line = malloc(max_len + 1);
	if (!new_line)
		return (NULL);
	memcpy(new_line, line, len);
	i = len;
	while (i < max_len)
	{
		new_line[i] = '1';
		i++;
	}
	new_line[max_len] = '\0';
	return (new_line);
}

void	pad_map(char **map_lines)
{
	int		max_len;
	int		i;
	char	*padded;

	i = 0;
	max_len = get_max_len(map_lines);
	while (map_lines[i])
	{
		padded = pad_line(map_lines[i], max_len);
		if (!padded)
			return ;
		free(map_lines[i]);
		map_lines[i] = padded;
		i++;
	}
}

void	cleanup(t_cub *cub)
{
	if (cub->map)
		free(cub->map);
	if (cub->map_lines)
		ft_free_split(cub->map_lines);
	free(cub->north_texture);
	free(cub->south_texture);
	free(cub->west_texture);
	free(cub->east_texture);
	free(cub->_F);
	free(cub->_C);
}
