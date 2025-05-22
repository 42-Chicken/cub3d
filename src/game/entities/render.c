/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:29:17 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/22 11:22:15 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2	get_draw_width(int width, int x)
{
	t_vec2	draw_x;

	draw_x.x = -width / 2 + x;
	if (draw_x.x < 0)
		draw_x.x = 0;
	draw_x.y = width / 2 + x;
	if (draw_x.y >= SCREEN_W)
		draw_x.y = SCREEN_W - 1;
	return (draw_x);
}

t_vec2	get_draw_height(int height)
{
	t_vec2	draw_y;

	draw_y.x = -height / 2 + SCREEN_H / 2;
	if (draw_y.x < 0)
		draw_y.x = 0;
	draw_y.y = height / 2 + SCREEN_H / 2;
	if (draw_y.y >= SCREEN_H)
		draw_y.y = SCREEN_H - 1;
	return (draw_y);
}

t_vec2	calculate_width_height_and_draw(t_dvec2 transformed, t_entity *entity,
		t_vec2 *draw_height, int x)
{
	entity->width = abs((int)(SCREEN_W / transformed.y)) * 1.2;
	entity->height = abs((int)(SCREEN_H / transformed.y)) * 1.7;
	*draw_height = get_draw_height(entity->height);
	return (get_draw_width(entity->width, x));
}

void	draw_entity(t_cub3d *cub3d, t_entity *entity, t_dvec2 transformed,
		int x)
{
	t_vec2		c;
	t_vec2		draw_width;
	t_vec2		draw_height;
	t_texture	*texture;
	t_uvec2		texture_pos;

	draw_width = calculate_width_height_and_draw(transformed, entity,
			&draw_height, x);
	texture = get_texture(cub3d, entity->textures[0]);
	c.x = draw_width.x - 1;
	while (++c.x < draw_width.y)
	{
		texture_pos.x = (int)(256 * (c.x - (-entity->width / 2 + x))
				* texture->width / entity->width) / 256;
		c.y = draw_height.x - 1;
		while (transformed.y > 0 && c.x > 0 && c.x < SCREEN_W && transformed.y
			* TILESIZE < cub3d->z_buffer[c.x] && ++c.y < draw_height.y)
		{
			texture_pos.y = (((double)((c.y) * 256 - SCREEN_H * 128
							+ entity->height * 128) *texture->height)
					/ entity->height) / 256;
			put_pixel_to_buffer(cub3d->rendering_buffer, (t_uvec2){(size_t)c.x,
				(size_t)c.y}, get_pixel_color(texture, texture_pos));
		}
	}
}

void	render_entities(t_cub3d *cub3d)
{
	size_t		i;
	t_dvec2		pos;
	t_dvec2		transformed;
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
		transformed = (t_dvec2){inv_det * (player.direction.y * pos.x
				- player.direction.x * pos.y), inv_det * (-player.plane.y
				* pos.x + player.plane.x * pos.y)};
		if (transformed.y > 0)
			draw_entity(cub3d, &cub3d->entities[i], transformed, (int)((SCREEN_W
						/ 2.0) * (1 + transformed.x / transformed.y)));
		i++;
	}
}
