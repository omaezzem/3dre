/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:36:42 by omaezzem          #+#    #+#             */
/*   Updated: 2025/12/03 17:47:40 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

size_t ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	return i;
}

void init_cub(t_cub *cub)
{
	cub->map = NULL;
	cub->texture = NULL;
	cub->NO = 0;
	cub->SO = 0;
	cub->WE = 0;
	cub->EA = 0;
	cub->F = 0;
	cub->C = 0;
	// These are the ones your raycasting uses
	cub->north_texture = NULL;
	cub->south_texture = NULL;
	cub->west_texture = NULL;
	cub->east_texture = NULL;
	cub->map_lines = NULL;
	cub->_F = NULL;
	cub->_C = NULL;
}

int pars_av(int ac, char **av)
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

void init_texture(char *path, t_cub *cub)
{
	if (strcmp(path, "NO") == 0)
		cub->NO += 1;
	else if (strcmp(path, "SO") == 0)
		cub->SO += 1;
	else if (strcmp(path, "WE") == 0)
		cub->WE += 1;
	else if (strcmp(path, "EA") == 0)
		cub->EA += 1;
	else if (strcmp(path, "F") == 0)
		cub->F += 1;
	else if (strcmp(path, "C") == 0)
		cub->C += 1;
}

int check_path(char *path)
{
	int i;

	if (!path)
		return (0);
	i = 0;
	while (path[i])
		i++;
	if (i < 5)  // Minimum: ".xpm" = 4 chars + at least 1 for filename
		return (0);
	i--;
	
	// Remove any trailing whitespace or newline
	while (i > 0 && (path[i] == ' ' || path[i] == '\t' || 
		path[i] == '\n' || path[i] == '\r'))
	{
		path[i] = '\0';
		i--;
	}
	
	// Check for .xpm extension (reading backwards: m, p, x, .)
	if (i >= 3 && path[i] == 'm' && path[i - 1] == 'p' &&
		path[i - 2] == 'x' && path[i - 3] == '.')
		return (1);
	
	// Also accept .png
	if (i >= 3 && path[i] == 'g' && path[i - 1] == 'n' &&
		path[i - 2] == 'p' && path[i - 3] == '.')
		return (1);
	
	return (0);
}

int is_empty_line(char *line)
{
	int i;
	
	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int is_path(char **split, t_cub *cub, char *line)
{
	if (!line || is_empty_line(line))
		return (1);
		
	if (!split || !split[0])
		return (1);

	// Handle color definitions
	if (strcmp(split[0], "F") == 0 || strcmp(split[0], "C") == 0)
	{
		if (!split[1])
		{
			fprintf(stderr, "Error: Missing color value for %s\n", split[0]);
			return (0);
		}
		init_texture(split[0], cub);
		return (1);
	}
	// Handle texture paths
	else if (strcmp(split[0], "NO") == 0 ||
		strcmp(split[0], "SO") == 0 ||
		strcmp(split[0], "WE") == 0 ||
		strcmp(split[0], "EA") == 0)
	{
		if (!split[1])
		{
			fprintf(stderr, "Error: Missing path for %s\n", split[0]);
			return (0);
		}
		if (!check_path(split[1]))
		{
			fprintf(stderr, "Error: Invalid texture extension for %s: '%s' (expected .xpm or .png)\n", 
				split[0], split[1]);
			return (0);
		}
		init_texture(split[0], cub);
		return (1);
	}
	// Handle map lines
	else
	{
		// Only start adding map lines after all textures are defined
		if (cub->NO != 1 || cub->SO != 1 || cub->WE != 1 || cub->EA != 1 ||
			cub->F != 1 || cub->C != 1)
			return (0);
		cub->map = ft_strjoin(cub->map, line);
	}
	return (1);
}

void join(t_cub *cub, char **path)
{
	char *cleaned;
	int i;
	
	if (!path || !path[0] || !path[1])
		return;
	
	// Create a clean copy without newlines
	cleaned = ft_strdup(path[1]);
	if (!cleaned)
		return;
		
	i = 0;
	while (cleaned[i])
	{
		if (cleaned[i] == '\n' || cleaned[i] == '\r')
		{
			cleaned[i] = '\0';
			break;
		}
		i++;
	}
	
	// Store in the correct variables that raycasting expects
	if (strcmp(path[0], "NO") == 0)
		cub->north_texture = cleaned;
	else if (strcmp(path[0], "SO") == 0)
		cub->south_texture = cleaned;
	else if (strcmp(path[0], "WE") == 0)
		cub->west_texture = cleaned;
	else if (strcmp(path[0], "EA") == 0)
		cub->east_texture = cleaned;
	else if (strcmp(path[0], "F") == 0)
		cub->_F = cleaned;
	else if (strcmp(path[0], "C") == 0)
		cub->_C = cleaned;
	else
		free(cleaned);
}

void clean_newline(char *str)
{
	int i;
	
	if (!str)
		return;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			break;
		}
		i++;
	}
}

int read_map(char *av, t_cub *cub)
{
	int fd;
	char *line;
	char **split;

	fd = open(av, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		split = ft_split(line, ' ');
		if (!is_path(split, cub, line))
		{
			fprintf(stderr, "Error: Invalid line: %s\n", line);
			if (split)
				free(split);
			free(line);
			close(fd);
			return (0);
		}
		join(cub, split);
		if (split)
			free(split);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	
	if (cub->NO != 1 || cub->SO != 1 || cub->WE != 1 || cub->EA != 1 ||
		cub->F != 1 || cub->C != 1)
	{
		fprintf(stderr, "Error: Missing textures or colors (NO=%d SO=%d WE=%d EA=%d F=%d C=%d)\n",
			cub->NO, cub->SO, cub->WE, cub->EA, cub->F, cub->C);
		return (0);
	}
	
	// Verify all texture paths were stored
	if (!cub->north_texture || !cub->south_texture || 
		!cub->west_texture || !cub->east_texture)
	{
		fprintf(stderr, "Error: Failed to store texture paths\n");
		return (0);
	}
	
	printf("\n=== Successfully parsed textures and colors ===\n");
	printf("North: %s\n", cub->north_texture);
	printf("South: %s\n", cub->south_texture);
	printf("West: %s\n", cub->west_texture);
	printf("East: %s\n", cub->east_texture);
	printf("Floor: %s\n", cub->_F);
	printf("Ceiling: %s\n", cub->_C);
	return (1);
}

int handle_colors_F(t_cub *cub)
{
	char **split;
	int i;
	int j;
	char *temp;

	if (!cub->_F)
		return (0);
	i = 0;
	temp = cub->_F;
	while (*temp)
	{
		if (*temp == ',')
			i++;
		temp++;
	}
	if (i != 2)
		return (0);
	split = ft_split(cub->_F, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (0);
	j = atoi(split[0]);
	if (j < 0 || j > 255)
		return (0);
	j = atoi(split[1]);
	if (j < 0 || j > 255)
		return (0);
	j = atoi(split[2]);
	if (j < 0 || j > 255)
		return (0);
	return (1);
}

int handle_colors_C(t_cub *cub)
{
	char **split;
	int i;
	int j;
	char *temp;

	if (!cub->_C)
		return (0);
	i = 0;
	temp = cub->_C;
	while (*temp)
	{
		if (*temp == ',')
			i++;
		temp++;
	}
	if (i != 2)
		return (0);
	split = ft_split(cub->_C, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (0);
	j = atoi(split[0]);
	if (j < 0 || j > 255)
		return (0);
	j = atoi(split[1]);
	if (j < 0 || j > 255)
		return (0);
	j = atoi(split[2]);
	if (j < 0 || j > 255)
		return (0);
	return (1);
}

int number_of_char(t_cub *cub)
{
	int i;
	int walls;
	int spaces;
	int players;

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
		else if (cub->map[i] == 'N' || cub->map[i] == 'S' ||
				cub->map[i] == 'E' || cub->map[i] == 'W')
			players++;
		i++;
	}
	if (walls < 1 || spaces < 1 || players != 1)
		return (0);
	return (1);
}

int pars_map(t_cub *cub)
{
	char **map_lines;
	int i;
	int j;

	if (!cub->map)
		return (0);
	map_lines = ft_split(cub->map, '\n');
	if (!map_lines)
		return (0);
	
	cub->map_lines = map_lines;
	
	// Check first line
	i = 0;
	while (map_lines[0][i])
	{
		if (map_lines[0][i] != '1' && map_lines[0][i] != ' ' && map_lines[0][i] != '\t')
			return (0);
		i++;
	}
	
	// Check middle lines
	j = 0;
	while (map_lines[j])
	{
		i = 0;
		if (map_lines[j][i] != '1' && map_lines[j][i] != ' ' && map_lines[j][i] != '\t')
			return (0);
		while (map_lines[j][i])
		{
			if (map_lines[j][i] != '1' && map_lines[j][i] != ' ' &&
				map_lines[j][i] != '\t' && map_lines[j][i] != '0' &&
				map_lines[j][i] != 'N' && map_lines[j][i] != 'S' &&
				map_lines[j][i] != 'E' && map_lines[j][i] != 'W')
				return (0);
			i++;
		}
		if (i > 0 && map_lines[j][i - 1] != '1' &&
			map_lines[j][i - 1] != ' ' && map_lines[j][i - 1] != '\t')
			return (0);
		if (map_lines[j + 1] == NULL)
			break;
		j++;
	}
	
	// Check last line
	i = 0;
	while (map_lines[j][i])
	{
		if (map_lines[j][i] != '1' && map_lines[j][i] != ' ' && map_lines[j][i] != '\t')
			return (0);
		i++;
	}
	
	if (!number_of_char(cub))
		return (0);
	return (1);
}

void change_space(t_cub *cub)
{
	int i;

	if (!cub->map)
		return;
	i = 0;
	while (cub->map[i])
	{
		if (cub->map[i] == ' ' || cub->map[i] == '\t')
			cub->map[i] = '1';
		i++;
	}
}

void find_p(t_cub *cub)
{
	int y;
	int x;
	int found;

	y = 0;
	found = 0;
	while (cub->map_lines[y])
	{
		x = 0;
		while (cub->map_lines[y][x])
		{
			if (cub->map_lines[y][x] == 'N' || cub->map_lines[y][x] == 'S' ||
				cub->map_lines[y][x] == 'E' || cub->map_lines[y][x] == 'W')
			{
				cub->player_pos.x = x;
				cub->player_pos.y = y;
				found = 1;
				break;
			}
			x++;
		}
		if (found)
			break;
		y++;
	}

	if (!found)
	{
		ft_putstr_fd("Error: Player not found in map\n", 2);
		exit(EXIT_FAILURE);
	}
}

void print_parsed_data(t_cub *cub)
{
	printf("\n=== Parsed Configuration ===\n");
	printf("North texture: %s\n", cub->north_texture ? cub->north_texture : "NULL");
	printf("South texture: %s\n", cub->south_texture ? cub->south_texture : "NULL");
	printf("West texture: %s\n", cub->west_texture ? cub->west_texture : "NULL");
	printf("East texture: %s\n", cub->east_texture ? cub->east_texture : "NULL");
	printf("Floor color: %s\n", cub->_F ? cub->_F : "NULL");
	printf("Ceiling color: %s\n", cub->_C ? cub->_C : "NULL");
	printf("\n=== Map ===\n%s\n", cub->map ? cub->map : "NULL");
}