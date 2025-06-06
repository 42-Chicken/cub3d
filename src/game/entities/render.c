/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:29:17 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/06 10:07:37 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color	fade_color(t_entity *entity, t_texture *texture, t_uvec2 pos)
{
	t_color	color;

	color = get_pixel_color(texture, pos);
	if (entity->max_health != 0 && color != 0xFF000000)
	{
		color = igmlx_melt_colors_weigthed(color, 0xFF0000, 1.0f
				- (double)entity->health / (double)entity->max_health);
	}
	if (entity->fade && color != 0xFF000000)
		return (igmlx_melt_colors_weigthed(color, 0x000000, 1
				- get_darkness(entity->distance_from_player * 50)));
	return (color);
}

void	draw_entity(t_cub3d *cub3d, t_entity *entity, int x)
{
	t_vec2		c;
	t_vec2		draw_width;
	t_vec2		dr_h;
	t_texture	*texture;
	t_uvec2		texture_pos;

	draw_width = calculate_width_height_and_draw(cub3d, entity, &dr_h, x);
	texture = get_entity_texture(cub3d, entity);
	c.x = draw_width.x - 1;
	while (++c.x < draw_width.y && !entity->not_displayed)
	{
		texture_pos.x = (int)(256 * (c.x - (-entity->width / 2 + x))
				* texture->width / entity->width) / 256;
		c.y = dr_h.x - 1;
		while (entity->transformed.y > 0 && c.x > 0 && c.x < SCREEN_W
			&& entity->transformed.y * TILESIZE < cub3d->z_buffer[c.x]
			&& ++c.y < dr_h.y)
		{
			texture_pos.y = (((double)((c.y - entity->y_offset) * 256 - SCREEN_H
							* 128 + entity->height * 128) *texture->height)
					/ entity->height) / 256;
			put_pixel_to_buffer(cub3d->rendering_buffer, (t_uvec2){(size_t)c.x,
				(size_t)c.y}, fade_color(entity, texture, texture_pos));
		}
	}
}

void	render_entities(t_cub3d *cub3d)
{
	size_t		i;
	t_dvec2		pos;
	double		inv_det;
	t_player	player;

	player = cub3d->player;
	i = 0;
	while (i < cub3d->entity_count)
	{
		pos = (t_dvec2){cub3d->entities[i].location.x - player.location.x,
			cub3d->entities[i].location.y - player.location.y};
		inv_det = 1.0 / (player.plane.x * player.direction.y
				- player.direction.x * player.plane.y);
		cub3d->entities[i].transformed = (t_dvec2){inv_det * (player.direction.y
				* pos.x - player.direction.x * pos.y), inv_det
			* (-player.plane.y * pos.x + player.plane.x * pos.y)};
		cub3d->entities[i].y_offset = (int)(-cub3d->entities[i].dst_from_floor
				* (cub3d->distance_from_camera
					/ cub3d->entities[i].transformed.y) / TILESIZE);
		if (cub3d->entities[i].transformed.y > 0 && cub3d->entities[i].in_game)
			draw_entity(cub3d, &cub3d->entities[i], (int)((SCREEN_W / 2.0) * (1
						+ cub3d->entities[i].transformed.x
						/ cub3d->entities[i].transformed.y)));
		i++;
	}
}
