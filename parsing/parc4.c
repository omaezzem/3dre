/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:25:18 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/21 17:09:48 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static char	*clean_newline_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
	return (str);
}

static void	set_texture_or_color(t_cub *cub, char *key, char *value)
{
	if (!key || !value)
		return ;
	if (strcmp(key, "NO") == 0)
		cub->north_texture = value;
	else if (strcmp(key, "SO") == 0)
		cub->south_texture = value;
	else if (strcmp(key, "WE") == 0)
		cub->west_texture = value;
	else if (strcmp(key, "EA") == 0)
		cub->east_texture = value;
	else if (strcmp(key, "F") == 0)
		cub->_F = value;
	else if (strcmp(key, "C") == 0)
		cub->_C = value;
	else
		free(value);
}

void	join(t_cub *cub, char **path)
{
	char	*cleaned;

	if (!path || !path[0] || !path[1])
		return ;
	cleaned = ft_strdup(path[1]);
	if (!cleaned)
		return ;
	cleaned = clean_newline_str(cleaned);
	set_texture_or_color(cub, path[0], cleaned);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	clean_newline(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
}
