/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 11:51:18 by omaezzem          #+#    #+#             */
/*   Updated: 2025/12/10 16:11:01 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

double	ft_calcul_vitaghors(t_cub *cub, double hit_x, double hit_y)
{
	double	dx;
	double	dy;

	dx = hit_x - cub->player.pos_x;
	dy = hit_y - cub->player.pos_y;
	return (sqrt(dx * dx + dy * dy));
}

static double	h_iteration_f(t_hcheck *h, t_cub *cub,
		double *hit_x, double *hit_y)
{
	while (h->iterations++ < 1000)
	{
		if (h->f_up)
			h->check_y = h->intersection_y - 1;
		else
			h->check_y = h->intersection_y;
		if (h->check_y < 0 || h->check_y >= cub->ray.map_y * T_SIZE
			|| h->intersection_x < 0 || h->intersection_x
			>= cub->ray.map_x * T_SIZE)
			break ;
		if (is_wall(cub, h->intersection_x, h->check_y))
		{
			*hit_x = h->intersection_x;
			*hit_y = h->intersection_y;
			return (ft_calcul_vitaghors(cub, h->intersection_x,
					h->intersection_y));
		}
		h->intersection_x += h->step_x;
		h->intersection_y += h->step_y;
	}
	return (1e30);
}

double	h_check(t_cub *cub, double *hit_x, double *hit_y, double angle)
{
	t_hcheck	h;

	h.f_up = (angle > M_PI && angle < 2 * M_PI);
	h.f_down = !h.f_up;
	h.intersection_y = floor(cub->player.pos_y / T_SIZE) * T_SIZE;
	if (h.f_down)
		h.intersection_y += T_SIZE;
	h.intersection_x = cub->player.pos_x
		+ (h.intersection_y - cub->player.pos_y) / tan(angle);
	h.step_y = T_SIZE;
	if (h.f_up)
		h.step_y = -T_SIZE;
	h.step_x = h.step_y / tan(angle);
	h.iterations = 0;
	return (h_iteration_f(&h, cub, hit_x, hit_y));
}

double	v_iteration_f(t_vcheck *v, t_cub *cub, double *hit_x, double *hit_y)
{
	while (v->iterations++ < 1000)
	{
		if (v->f_left)
			v->check_x = v->intersection_x - 1;
		else
			v->check_x = v->intersection_x;
		if (v->check_x < 0 || v->check_x >= cub->ray.map_x * T_SIZE
			|| v->intersection_y < 0 || v->intersection_y
			>= cub->ray.map_y * T_SIZE)
			break ;
		if (is_wall(cub, v->check_x, v->intersection_y))
		{
			*hit_x = v->intersection_x;
			*hit_y = v->intersection_y;
			return (ft_calcul_vitaghors(cub,
					v->intersection_x, v->intersection_y));
		}
		v->intersection_x += v->step_x;
		v->intersection_y += v->step_y;
	}
	return (1e30);
}

double	v_check(t_cub *cub, double *hit_x, double *hit_y, double angle)
{
	t_vcheck	v;

	v.f_left = (angle > M_PI / 2 && angle < 3 * M_PI / 2);
	v.f_right = !v.f_left;
	v.intersection_x = floor(cub->player.pos_x / T_SIZE) * T_SIZE;
	if (v.f_right)
		v.intersection_x += T_SIZE;
	v.intersection_y = cub->player.pos_y
		+ (v.intersection_x - cub->player.pos_x) * tan(angle);
	v.step_x = T_SIZE;
	if (v.f_left)
		v.step_x = -T_SIZE;
	v.step_y = v.step_x * tan(angle);
	v.iterations = 0;
	return (v_iteration_f(&v, cub, hit_x, hit_y));
}
