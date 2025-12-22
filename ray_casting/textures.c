/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:13:11 by omaezzem          #+#    #+#             */
/*   Updated: 2025/12/20 14:30:40 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	update_weapon(t_cub *cub)
{
	static int delay = 0;

	delay++;
	if (delay < 2)
		return;

	delay = 0;
	cub->weapon.current++;
	if (cub->weapon.current >= cub->weapon.frame_count)
		cub->weapon.current = 0;
}

void	draw_weapon(t_cub *cub)
{
	t_texture	*tex;
	int			x;
	int			y;
	int			start_x;
	int			start_y;
	int			color;

	tex = &cub->weapon.frames[cub->weapon.current];
	start_x = (WIDTH / 2) - (tex->width / 2);
	start_y = HEIGHT - tex->height;
	y = 0;
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			color = get_texture_color(tex, x, y);
			if ((color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(cub, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	load_weapon(t_cub *cub)
{
	int		i;
	char	path[64];

	cub->weapon.frame_count = 8;
	cub->weapon.current = 0;
	cub->weapon.animating = 0;
	i = 0;
	while (i < cub->weapon.frame_count)
	{
		sprintf(path, "imgs/m%d.xpm", i);
		load_texture(cub, &cub->weapon.frames[i], path);
		i++;
	}
}

void	load_textures(t_cub *cub)
{	
	if (!cub->north_texture || !cub->south_texture
		|| !cub->east_texture || !cub->west_texture)
	{
		ft_putstr_fd("Error\nMissing texture paths\n", 2);
		exit(EXIT_FAILURE);
	}
	if (cub->north_texture)
		load_texture(cub, &cub->tex_north, cub->north_texture);
	if (cub->south_texture)
		load_texture(cub, &cub->tex_south, cub->south_texture);
	if (cub->east_texture)
		load_texture(cub, &cub->tex_east, cub->east_texture);
	if (cub->west_texture)
		load_texture(cub, &cub->tex_west, cub->west_texture);
	load_weapon(cub);
}

void	load_texture(t_cub *cub, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		ft_putstr_fd("Error\nFailed to load texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		ft_putstr_fd("Error\nFailed to get texture data: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
	}
}

t_texture	*get_wall_texture(t_cub *cub, double ray_angle, int is_vertical)
{
	while (ray_angle < 0)
		ray_angle += 2 * M_PI;
	while (ray_angle >= 2 * M_PI)
		ray_angle -= 2 * M_PI;
	if (is_vertical)
	{
		if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
			return (&cub->tex_west);
		else
			return (&cub->tex_east);
	}
	else
	{
		if (ray_angle > M_PI && ray_angle < 2 * M_PI)
			return (&cub->tex_north);
		else
			return (&cub->tex_south);
	}
}

int	get_texture_color(t_texture *tex, int tex_x, int tex_y)
{
	char	*pixel;

	if (!tex || !tex->img || !tex->addr)
		return (0);
	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	ft_loop_tex(t_wall_tex *wt, t_render *r, t_cub *cub)
{
	wt->y = r->wall_top;
	while (wt->y < wt->wall_bottom)
	{
		if (wt->texture && wt->texture->img && wt->texture->addr)
		{
			wt->tex_y = (int)wt->tex_pos;
			wt->color = get_texture_color(wt->texture,
					wt->tex_x, wt->tex_y);
			my_mlx_pixel_put(cub, r->i, wt->y, wt->color);
			wt->tex_pos += wt->step;
		}
		wt->y++;
	}
}
