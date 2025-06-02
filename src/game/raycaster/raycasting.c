/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:43:43 by efranco           #+#    #+#             */
/*   Updated: 2025/06/02 16:02:31 by rguigneb         ###   ########.fr       */
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

void get_wall_hit(t_cub3d *data, t_ray *ray)
{
    double hor_dist;
    double vert_dist;

    // Set separate skip counters
    ray->skip_horizontal = ray->o_skip_horizontal;
    ray->skip_vertical = ray->o_skip_vertical;

    get_horizontal_intersection(data, ray);
    get_vertical_intersection(data, ray);

    // Rest of your distance calculation logic...
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

void render_raycasting(t_cub3d *data)
{
    t_ray ray;
    double angle;
    size_t i;
    double angle_step = data->fov / data->num_rays;

    i = 0;
    angle = data->player.rotation_angle - data->fov / 2;

    while (i < data->num_rays)
    {
        // Initialize ray once
        ft_bzero(&ray, sizeof(t_ray));
        angle += angle_step;
        ray.rayangle = normalizeangle(angle);
        ray.x = i;
        ray.o_skip_horizontal = 0;
        ray.o_skip_vertical = 0;

        // Get wall hit once and cache results
        get_wall_hit(data, &ray);
        char base_wall = ray.wall;
        double base_height = get_wall_type_height(base_wall);

        // Find the appropriate wall to render
        size_t skip = 1;
        t_ray temp_ray = ray; // Copy instead of recalculating

        while (skip < 6)
        {
            ft_bzero(&temp_ray, sizeof(t_ray));
            temp_ray.rayangle = normalizeangle(angle);
            temp_ray.x = i;

            // Set skip counters based on which wall type we found in base ray
            if (ray.was_hit_vertical)
            {
                temp_ray.o_skip_horizontal = 0;
                temp_ray.o_skip_vertical = skip;
            }
            else
            {
                temp_ray.o_skip_horizontal = skip;
                temp_ray.o_skip_vertical = 0;
            }

            get_wall_hit(data, &temp_ray);

            if (get_wall_type_height(temp_ray.wall) > base_height)
            {
                draw_wall(data, &temp_ray);
                break;
            }
            skip++;
        }
        draw_wall(data, &ray);

        data->z_buffer[i] = ray.distance;
        i++;
    }
}
