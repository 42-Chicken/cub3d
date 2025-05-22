/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:43:43 by efranco           #+#    #+#             */
/*   Updated: 2025/05/22 09:57:00 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ray_hit_vertical_wall(t_cub3d *data, t_ray *ray, double vert_dist)
{
	double	angle_diff;

	angle_diff = ray->rayangle - data->player.rotation_angle;
	ray->distance = vert_dist * cos(angle_diff);
	ray->was_hit_vertical = true;
	ray->wall_hit_x = ray->vertical_hit_x;
	ray->wall_hit_y = ray->vertical_hit_y;
	if (ray->rayangle >= M_PI / 2 && ray->rayangle <= M_PI + M_PI / 2)
		ray->facing_wall = WEST;
	else
		ray->facing_wall = EAST;
}

static void	ray_hit_horizontal_wall(t_cub3d *data, t_ray *ray, double hor_dist)
{
	double	angle_diff;

	angle_diff = ray->rayangle - data->player.rotation_angle;
	ray->distance = hor_dist * cos(angle_diff);
	ray->was_hit_vertical = false;
	ray->wall_hit_x = ray->horizontal_hit_x;
	ray->wall_hit_y = ray->horizontal_hit_y;
	if (ray->rayangle >= 0 && ray->rayangle <= M_PI)
		ray->facing_wall = NORTH;
	else
		ray->facing_wall = SOUTH;
}

void	get_wall_hit(t_cub3d *data, t_ray *ray)
{
	double	hor_dist;
	double	vert_dist;

	get_horizontal_intersection(data, ray);
	get_vertical_intersection(data, ray);
	if (ray->found_horizontal_wall)
		hor_dist = fdistance_between(data->player.location.x * TILESIZE,
				data->player.location.y * TILESIZE, ray->horizontal_hit_x,
				ray->horizontal_hit_y);
	else
		hor_dist = 99999;
	if (ray->found_vertical_wall)
		vert_dist = fdistance_between(data->player.location.x * TILESIZE,
				data->player.location.y * TILESIZE, ray->vertical_hit_x,
				ray->vertical_hit_y);
	else
		vert_dist = 99999;
	if (vert_dist < hor_dist)
		ray_hit_vertical_wall(data, ray, vert_dist);
	else
		ray_hit_horizontal_wall(data, ray, hor_dist);
	ray->wall = map_get_wall(data, ray->wall_hit_x / TILESIZE, ray->wall_hit_y
			/ TILESIZE);
}

void	render_raycasting(t_cub3d *data)
{
	t_ray	ray;
	double	angle;
	int		i;

	i = 0;
	angle = data->player.rotation_angle - FOV / 2;
	while (i < NUM_RAYS)
	{
		ft_bzero(&ray, sizeof(t_ray));
		ray.rayangle = normalizeangle(angle);
		ray.x = i;
		angle += FOV / NUM_RAYS;
		get_wall_hit(data, &ray);
		data->z_buffer[i] = ray.distance;
		draw_wall(data, &ray);
		i++;
	}
}
