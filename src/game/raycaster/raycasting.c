/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:43:43 by efranco           #+#    #+#             */
/*   Updated: 2025/06/05 09:11:18 by rguigneb         ###   ########.fr       */
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
	t_ray	ray[2];
	double	angle;
	size_t	i;
	double	base_height;
	double	angle_step;

	angle_step = data->fov / data->num_rays;
	i = -1;
	angle = data->player.rotation_angle - data->fov / 2;
	while (++i < data->num_rays)
	{
		ft_bzero(&ray, sizeof(t_ray) * 2);
		angle += angle_step;
		ray[0].rayangle = normalizeangle(angle);
		ray[0].x = i;
		get_wall_hit(data, &ray[0]);
		base_height = get_wall_type_height(ray[0].wall);
		ray[1].rayangle = normalizeangle(angle);
		ray[1].x = i;
		ray[1].min_height = base_height;
		get_wall_hit(data, &ray[1]);
		draw_wall(data, &ray[0], &ray[1]);
	}
}
