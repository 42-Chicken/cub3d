/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:32:07 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/03 10:31:55 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_wall_type_height(char c)
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
	if (*begin < 0)
		*begin = 0;
	if (*begin > SCREEN_H)
		*begin = SCREEN_H;
}

void	draw_wall(t_cub3d *data, t_ray *ray, t_ray *temp_ray)
{
	double	height;
	double	draw_begin;
	double	temp_height;
	double	temp_draw_begin;

	ray->standard_wall_height = ((double)(64 / ray->distance)
			* data->distance_from_camera);
	ray->floor_start = SCREEN_H / 2 + ray->standard_wall_height / 2;
	temp_ray->standard_wall_height = ((double)(64 / temp_ray->distance)
			* data->distance_from_camera);
	temp_ray->floor_start = SCREEN_H / 2 + temp_ray->standard_wall_height / 2;
	calculate_begin_and_height(data, ray, &height, &draw_begin);
	calculate_begin_and_height(data, temp_ray, &temp_height, &temp_draw_begin);
	draw_sky(data, temp_ray, temp_draw_begin);
	temp_ray->floor_start = draw_begin;
	draw_textured_wall(data, temp_ray, temp_draw_begin, temp_height / 2);
	ray->skip = 0;
	draw_textured_wall(data, ray, draw_begin, height / 2);
	draw_floor(data, ray);
	data->z_buffer[ray->x] = ray->distance;
}
