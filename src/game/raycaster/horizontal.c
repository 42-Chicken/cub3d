/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:59:16 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/03 09:09:31 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_dvec2	get_horizontal_intercept(t_cub3d *data, double angle)
{
	t_dvec2	intercept;

	intercept.y = floor(data->player.location.y * TILESIZE / TILESIZE)
		* TILESIZE;
	if (angle > 0 && angle < M_PI)
		intercept.y += TILESIZE;
	intercept.x = data->player.location.x * TILESIZE + (intercept.y
			- data->player.location.y * TILESIZE) / tan(angle);
	return (intercept);
}

static t_dvec2	get_horizontal_step(double angle)
{
	t_dvec2	step;

	if (angle > 0 && angle < M_PI)
		step.y = TILESIZE;
	else
		step.y = -TILESIZE;
	step.x = TILESIZE / tan(angle);
	if ((angle > M_PI_2 && angle < 3 * M_PI_2) && step.x > 0)
		step.x *= -1;
	if (!(angle > M_PI_2 && angle < 3 * M_PI_2) && step.x < 0)
		step.x *= -1;
	return (step);
}

static bool	wall_handler(t_cub3d *data, t_ray *ray, t_dvec2 next, float check_y)
{
	char	c;

	if (map_is_wall(data, next.x / TILESIZE, check_y / TILESIZE))
	{
		c = map_get_wall(data, next.x / TILESIZE, check_y / TILESIZE);
		if (get_wall_type_height(c) > ray->min_height)
		{
			ray->horizontal_hit_x = next.x;
			ray->horizontal_hit_y = check_y;
			ray->found_horizontal_wall = true;
			return (true);
		}
	}
	return (false);
}

void	get_horizontal_intersection(t_cub3d *data, t_ray *ray)
{
	float	angle;
	t_dvec2	step;
	t_dvec2	next;
	float	check_y;

	angle = ray->rayangle;
	next = get_horizontal_intercept(data, angle);
	step = get_horizontal_step(angle);
	while (next.x >= 0 && next.x <= data->map.width * TILESIZE && next.y >= 0
		&& next.y <= data->map.height * TILESIZE)
	{
		if (angle > 0 && angle < M_PI)
			check_y = next.y;
		else
			check_y = next.y - 0.001f;
		if (wall_handler(data, ray, next, check_y))
			break ;
		next.x += step.x;
		next.y += step.y;
	}
}
