/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:20:50 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 08:31:00 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(t_cub3d *data, t_ray *ray, double height, double begin)
{
	double	row_distance;
	size_t	y;
	t_dvec2	floor;
	t_vec2	texture_loc;
	t_img	*img;

	img = get_texture(data, TEXTURE_WALL_DEFAULT);
	y = (int)height + begin - 1;
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
		put_pixel_to_buffer(data->rendering_buffer, (t_uvec2){ray->x, y},
			get_pixel_color(img, (t_uvec2){texture_loc.x, texture_loc.y}));
	}
}
