/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:32:07 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/21 09:45:44 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_wall_height(double distance)
{
	return ((double)(64 / distance) *DISTANCE_FROM_CAMERA);
}

static void	calculate_begin_and_height(t_ray *ray, double *height,
		double *begin)
{
	*height = get_wall_height(ray->distance);
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

	calculate_begin_and_height(ray, &height, &draw_begin);
	draw_sky(data, ray, draw_begin);
	draw_textured_wall(data, ray, draw_begin, height / 2);
	draw_floor(data, ray, height, draw_begin);
}
