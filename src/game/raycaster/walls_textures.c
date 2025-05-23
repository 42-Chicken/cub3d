/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:42:21 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 10:55:55 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	*get_wall_texture(t_cub3d *cub3d, t_ray *ray)
{
	t_texture	*texture;

	if (ray->wall == CUB3D_MAP_WALL)
	{
		if (ray->facing_wall == NORTH)
			texture = get_texture(cub3d, TEXTURE_WALL_NORTH);
		if (ray->facing_wall == SOUTH)
			texture = get_texture(cub3d, TEXTURE_WALL_SOUTH);
		if (ray->facing_wall == EAST)
			texture = get_texture(cub3d, TEXTURE_WALL_EAST);
		if (ray->facing_wall == WEST)
			texture = get_texture(cub3d, TEXTURE_WALL_WEST);
	}
	else
	{
		texture = get_linked_texture(cub3d, ray->wall);
		if (!texture)
			texture = get_texture(cub3d, TEXTURE_WALL_DEFAULT);
	}
	return (texture);
}

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

static double	get_texture_x(t_texture *texture, t_ray *ray)
{
	double	x;

	if (ray->was_hit_vertical)
		x = (int)floor(ray->wall_hit_y) % texture->width;
	else
		x = (int)floor(ray->wall_hit_x) % texture->width;
	x = (x * texture->width) / texture->width;
	return (x);
}

static t_color	get_texture_pixel_color(t_texture *texture, t_uvec2 loc,
		double darkness_weight)
{
	t_color	color;

	color = get_pixel_color(texture, loc);
	color = igmlx_melt_colors_weigthed(0x000000, color, darkness_weight);
	return (color);
}

void	draw_textured_wall(t_cub3d *data, t_ray *ray, double begin,
		double half_height)
{
	double		distance_top;
	t_texture	*wall_texture;
	double		darkness_weight;
	t_uvec2		texture_loc;
	size_t		y;

	y = begin;
	darkness_weight = get_darkness(ray->distance);
	wall_texture = get_wall_texture(data, ray);
	texture_loc.x = get_texture_x(wall_texture, ray);
	half_height = get_wall_height(data, ray->distance) / 2;
	while (y < SCREEN_H - begin)
	{
		distance_top = y + (half_height) - (SCREEN_H / 2);
		texture_loc.y = (1LL * distance_top * wall_texture->height
				+ half_height) / (half_height * 2);
		texture_loc.y = texture_loc.y % wall_texture->height;
		put_pixel_to_buffer(data->rendering_buffer, (t_uvec2){ray->x, y},
			(int)get_texture_pixel_color(wall_texture, texture_loc,
				darkness_weight));
		y++;
	}
}
