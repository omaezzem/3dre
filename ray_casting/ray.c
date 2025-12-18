/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:37:22 by omaezzem          #+#    #+#             */
/*   Updated: 2025/12/10 16:06:07 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../cub.h"

void	init_player_raycasting(t_cub *cub)
{
	char	o;

	cub->ray.map_x = ft_strlen(cub->map_lines[0]);
	cub->ray.map_y = len_h(cub->map_lines);
	o = cub->map_lines[cub->player_pos.y][cub->player_pos.x];
	cub->player.pos_x = cub->player_pos.x * T_SIZE + T_SIZE / 2;
	cub->player.pos_y = cub->player_pos.y * T_SIZE + T_SIZE / 2;
	if (o == 'N')
		cub->player.angle = 3 * M_PI / 2;
	else if (o == 'S')
		cub->player.angle = M_PI / 2;
	else if (o == 'E')
		cub->player.angle = 0;
	else if (o == 'W')
		cub->player.angle = M_PI;
	else
	{
		ft_putstr_fd("Error: invalid player orientation\n", 2);
		exit(EXIT_FAILURE);
	}
}

double	ft_casting(t_cub *cub, double angle, int *is_vertical)
{
	double	h_distance;
	double	v_distance;

	cub->cast.h_hitx = 0;
	cub->cast.h_hity = 0;
	cub->cast.v_hitx = 0;
	cub->cast.v_hity = 0;
	h_distance = h_check(cub, &cub->cast.h_hitx, &cub->cast.h_hity, angle);
	v_distance = v_check(cub, &cub->cast.v_hitx, &cub->cast.v_hity, angle);
	if (v_distance < h_distance)
	{
		*is_vertical = 1;
		return (v_distance);
	}
	else
	{
		*is_vertical = 0;
		return (h_distance);
	}
}

void	draw_vertical_wall_strip(t_cub *cub, t_render *r)
{
	t_wall_tex	wt;

	wt.original_wall_top = 0;
	wt.original_wall_top = r->wall_top;
	wt.wall_bottom = r->wall_top + r->wall_height;
	wt.texture = get_wall_texture(cub, r->ray_angle, r->is_vertical);
	if (r->is_vertical)
	{
		wt.wall_hit_x = cub->cast.v_hity;
	}
	else
	{
		wt.wall_hit_x = cub->cast.h_hitx;
	}
	wt.wall_hit_x = fmod(wt.wall_hit_x, T_SIZE) / T_SIZE;
	if (wt.texture && wt.texture->img && wt.texture->width > 0)
		wt.tex_x = (int)(wt.wall_hit_x * wt.texture->width);
	if (wt.texture && wt.texture->img && r->wall_height > 0)
		wt.step = (double)wt.texture->height / (double)r->wall_height;
	wt.tex_pos = 0;
	ft_loop_tex(&wt, r, cub);
}

void	ft_loop_ray(t_render *r, t_cub *cub)
{
	while (r->i < WIDTH)
	{

		r->ray_angle = cub->player.angle - (FOV / 2.0)
			+ ((double)r->i * FOV / (double)WIDTH);
		checker_ray_angle(r);
		r->distance = ft_casting(cub, r->ray_angle, &r->is_vertical);
		r->corrected_distance = r->distance * cos(r->ray_angle
				- cub->player.angle);
		r->wall_height = (T_SIZE / r->corrected_distance)
			* r->projection_distance;
		r->wall_top = (HEIGHT / 2.0) - (r->wall_height / 2.0);
		draw_vertical_wall_strip(cub, r);
		draw_ceiling_floor_column(cub, r->i, (int)r->wall_top,
			(int)r->wall_top + (int)r->wall_height);
		r->i++;
	}
}

void	draw_frame(t_cub *cub)
{
	t_render	r;

	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		exit(ft_error("mlx_new_image failed"));
	cub->addr = mlx_get_data_addr(cub->img, &cub->bpp,
			&cub->line_len, &cub->endian);
	if (!cub->addr)
	{
		mlx_destroy_image(cub->mlx, cub->img);
		exit(ft_error("mlx_get_data_addr failed"));
	}

	r.projection_distance = (WIDTH / 2.0) / tan(FOV / 2.0);
	r.i = 0;
	ft_loop_ray(&r, cub);
	update_weapon(cub);
	draw_weapon(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->img);
}
