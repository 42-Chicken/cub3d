/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:32:07 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/22 16:23:32 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_wall_height(t_cub3d *data, double distance)
{
	return ((double)(64 / distance) *data->distance_from_camera);
}

static void	calculate_begin_and_height(t_cub3d *data, t_ray *ray,
		double *height, double *begin)
{
	*height = get_wall_height(data, ray->distance);
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

void	draw_wall(t_cub3d *data, t_ray *ray)
{
	double	height;
	double	draw_begin;

	calculate_begin_and_height(data, ray, &height, &draw_begin);
	draw_sky(data, ray, draw_begin);
	draw_textured_wall(data, ray, draw_begin, height / 2);
	draw_floor(data, ray, height, draw_begin);
}
