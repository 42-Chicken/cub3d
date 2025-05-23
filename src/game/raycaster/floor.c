/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:20:50 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 12:42:28 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_darkness(double distance)
{
	double	darkness_weight;

	darkness_weight = (215 / distance);
	if (darkness_weight < 0)
		darkness_weight = 0;
	if (darkness_weight > 1)
		darkness_weight = 1;
	return (darkness_weight);
}

static void	draw_floor_pixel_color(t_cub3d *data, t_uvec2 pos,
		t_color pixel_color, double row_distance)
{
	put_pixel_to_buffer(data->rendering_buffer, pos,
		igmlx_melt_colors_weigthed(0x000000, pixel_color,
			get_darkness(row_distance * 100)));
}

void	draw_floor(t_cub3d *data, t_ray *ray, double height, double begin)
{
	double	row_distance;
	size_t	y;
	t_dvec2	floor;
	t_vec2	texture_loc;
	t_img	*img;
	double	standard_wall_height;
	double	floor_start;

	(void)height;
	(void)begin;
	img = get_texture(data, TEXTURE_FLOOR);
	standard_wall_height = ((double)(64 / ray->distance)
			* data->distance_from_camera);
	floor_start = SCREEN_H / 2 + standard_wall_height / 2;
	y = (int)floor_start - 1;
	ray->dir_x = cos(ray->rayangle);
	ray->dir_y = sin(ray->rayangle);
	while (++y < SCREEN_H)
	{
		row_distance = ((data->distance_from_camera * 0.5f) / ((float)y
					- (SCREEN_H / 2))) / cos(ray->rayangle
				- data->player.rotation_angle);
		floor = (t_dvec2){
			data->player.location.x + row_distance * ray->dir_x,
			data->player.location.y + row_distance * ray->dir_y,
		};
		texture_loc = (t_vec2){(int)(floor.x * img->width) % img->width,
			(int)(floor.y * img->height) % img->height};
		draw_floor_pixel_color(data, (t_uvec2){ray->x, y}, get_pixel_color(img,
				(t_uvec2){texture_loc.x, texture_loc.y}), row_distance);
	}
}
