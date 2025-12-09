/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:27:03 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/06 17:56:38 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	open_file(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		perror("Error opening file");
	return (fd);
}

static int	process_line(t_cub *cub, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (0);
	if (!is_path(split, cub, line))
	{
		fprintf(stderr, "Error: Invalid line: %s\n", line);
		ft_free_split(split);
		return (0);
	}
	join(cub, split);
	ft_free_split(split);
	return (1);
}

static int	check_textures(t_cub *cub)
{
	if (cub->NO != 1 || cub->SO != 1 || cub->WE != 1 || cub->EA != 1
		|| cub->F != 1 || cub->C != 1)
	{
		fprintf(stderr, "Error: Missing textures or colors \
		(NO=%d SO=%d WE=%d EA=%d F=%d C=%d)\n",
			cub->NO, cub->SO, cub->WE, cub->EA, cub->F, cub->C);
		return (0);
	}
	if (!cub->north_texture || !cub->south_texture
		|| !cub->west_texture || !cub->east_texture)
	{
		fprintf(stderr, "Error: Failed to store texture paths\n");
		return (0);
	}
	return (1);
}

static void	print_textures(t_cub *cub)
{
	printf("\n=== Successfully parsed textures and colors ===\n");
	printf("North: %s\n", cub->north_texture);
	printf("South: %s\n", cub->south_texture);
	printf("West: %s\n", cub->west_texture);
	printf("East: %s\n", cub->east_texture);
	printf("Floor: %s\n", cub->_F);
	printf("Ceiling: %s\n", cub->_C);
}

int	read_map(char *av, t_cub *cub)
{
	int		fd;
	char	*line;

	fd = open_file(av);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(cub, line))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!check_textures(cub))
		return (0);
	print_textures(cub);
	return (1);
}
