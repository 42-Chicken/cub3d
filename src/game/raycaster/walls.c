/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:32:07 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/02 12:29:39 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double get_wall_type_height(char c)
{
	double	base_height;

	base_height = 850;
	if (c == 'G')
	{
		base_height = 135;
	}
	if (c == 'F')
	{
		base_height = 400;
	}
	if (c == CUB3D_MAP_BUILDING)
	{
		base_height = 350;
	}
	return (base_height);
}

double	get_wall_height(t_cub3d *data, t_ray *ray)
{
	double	base_height;

	base_height = get_wall_type_height(ray->wall);
	return ((double)(base_height / ray->distance) * data->distance_from_camera);
}

static void	calculate_begin_and_height(t_cub3d *data, t_ray *ray,
		double *height, double *begin)
{
	*height = get_wall_height(data, ray);
	if (*height < 0)
		*height = 0;
	if (*height > SCREEN_H)
		*height = SCREEN_H;
	*begin = (SCREEN_H - *height) / 2;
	if (ray->wall == CUB3D_MAP_TOWNHALL)
	{
		*begin -= *height / 4;
	}
	if (*begin < 0)
		*begin = 0;
	if (*begin > SCREEN_H)
		*begin = SCREEN_H;
}

void	draw_wall(t_cub3d *data, t_ray *ray)
{
	double	height;
	double	draw_begin;

	calculate_begin_and_height(data, ray, &height, &draw_begin);
	// if (ray->o_skip == 1)
	// 	draw_sky(data, ray, draw_begin);
	draw_textured_wall(data, ray, draw_begin, height / 2);
	if (ray->o_skip == 0)
		draw_floor(data, ray, height, draw_begin);
}
