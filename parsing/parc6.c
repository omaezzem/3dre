/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:27:49 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/21 17:45:19 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	count_commas(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == ',')
			i++;
		str++;
	}
	return (i);
}

static int	validate_rgb(char **split)
{
	int	i;
	int	val;
	int	j;

	i = 0;
	while (i < 3)
	{
		if (!split[i])
			return (0);
		j = 0;
		while (split[i][j])
		{
			if (!ft_isdigit(split[i][j]))
				return (0);
			j++;
		}
		val = ft_atoi(split[i]);
		if (val < 0 || val > 225)
			return (0);
		i++;
	}
	return (1);
}

int	handle_colors_str(char *color)
{
	char	**split;
	int		ret;

	if (!color || count_commas(color) != 2)
		return (0);
	split = ft_split(color, ',');
	if (!split)
		return (0);
	ret = validate_rgb(split);
	if (!ret)
	{
		ft_free_split(split);
		return (0);
	}
	ft_free_split(split);
	return (ret);
}

int	ft_split_len(char **split)
{
	int	len;

	len = 0;
	if (!split)
		return (0);
	while (split[len])
		len++;
	return (len);
}

int	number_of_char(t_cub *cub)
{
	int	i;
	int	walls;
	int	spaces;
	int	players;

	if (!cub->map)
		return (0);
	i = 0;
	walls = 0;
	spaces = 0;
	players = 0;
	while (cub->map[i])
	{
		if (cub->map[i] == '1')
			walls++;
		else if (cub->map[i] == '0')
			spaces++;
		else if (cub->map[i] == 'N' || cub->map[i] == 'S'
			|| cub->map[i] == 'E' || cub->map[i] == 'W')
			players++;
		i++;
	}
	if (walls < 1 || spaces < 1 || players != 1)
		return (0);
	return (1);
}
