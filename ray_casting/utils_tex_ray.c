/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tex_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:15:56 by omaezzem          #+#    #+#             */
/*   Updated: 2025/12/22 16:32:22 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_ceiling_floor_column(t_cub *cub, int x,
		int wall_top, int wall_bottom)
{
	int	y;

	y = 0;
	while (y < wall_top && y < HEIGHT)
	{
		my_mlx_pixel_put(cub, x, y, cub->C);
		y++;
	}
	y = wall_bottom;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(cub, x, y, cub->F);
		y++;
	}
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	checker_ray_angle(t_render *r)
{
	while (r->ray_angle < 0)
		r->ray_angle += 2 * M_PI;
	while (r->ray_angle >= 2 * M_PI)
		r->ray_angle -= 2 * M_PI;
}

int	is_wall(t_cub *cub, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / T_SIZE);
	map_y = (int)(y / T_SIZE);
	if (map_x < 0 || map_y < 0
		|| map_x >= cub->ray.map_x
		|| map_y >= cub->ray.map_y)
		return (1);
	return (cub->map_lines[map_y][map_x] == '1');
}

void	my_mlx_pixel_put(t_cub *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}
