/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:53:24 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/21 10:03:28 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_dvec2	get_vertical_intercept(t_cub3d *data, double angle)
{
	t_dvec2	intercept;

	intercept.x = floor(data->player.location.x * TILESIZE / TILESIZE)
		* TILESIZE;
	if (angle < M_PI_2 || angle > 3 * M_PI_2)
		intercept.x += TILESIZE;
	intercept.y = data->player.location.y * TILESIZE + (intercept.x
			- data->player.location.x * TILESIZE) * tan(angle);
	return (intercept);
}

static t_dvec2	get_vertical_step(double angle)
{
	t_dvec2	step;

	if (angle < M_PI_2 || angle > 3 * M_PI_2)
		step.x = TILESIZE;
	else
		step.x = -TILESIZE;
	step.y = TILESIZE * tan(angle);
	if (angle > M_PI && step.y > 0)
		step.y *= -1;
	if (angle < M_PI && step.y < 0)
		step.y *= -1;
	return (step);
}

void	get_vertical_intersection(t_cub3d *data, t_ray *ray)
{
	double	angle;
	t_dvec2	next;
	t_dvec2	step;
	float	check_x;

	angle = ray->rayangle;
	next = get_vertical_intercept(data, angle);
	step = get_vertical_step(angle);
	while (next.x >= 0 && next.x <= data->map.width * TILESIZE && next.y >= 0
		&& next.y <= data->map.height * TILESIZE)
	{
		if (angle < M_PI_2 || angle > 3 * M_PI_2)
			check_x = next.x;
		else
			check_x = next.x - 0.001f;
		if (map_is_wall(data, check_x / TILESIZE, next.y / TILESIZE))
		{
			ray->vertical_hit_x = check_x;
			ray->vertical_hit_y = next.y;
			ray->found_vertical_wall = true;
			break ;
		}
		next.x += step.x;
		next.y += step.y;
	}
}
