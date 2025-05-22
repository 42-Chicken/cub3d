/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:29:17 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/22 10:00:39 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_entities(t_cub3d *cub3d)
{
	size_t	i;
	int	j;
	int	k;
	t_entity *entity;
	t_dvec2 pos;
	t_dvec2 transformed;
	double inv_det;
	double plane_len = tan(FOV * 0.5);
	const t_dvec2 plane = (t_dvec2){plane_len * -cub3d->player.sin_r, plane_len * cub3d->player.cos_r };
	const t_dvec2 direction = (t_dvec2){cub3d->player.cos_r, cub3d->player.sin_r};
	int x;
	int height;
	int width;
	t_vec2 draw_y;
	t_vec2 draw_x;
	t_uvec2 texture_pos;
	t_texture	*texture;
	int d;

	i = 0;
	while (i < MAX_ENTITIES)
	{
		entity = &cub3d->entities[i];
		texture = get_texture(cub3d, entity->textures[0]);
		pos = (t_dvec2){entity->location.x - cub3d->player.location.x, entity->location.y - cub3d->player.location.y};
		inv_det = 1.0 / (plane.x * direction.y - direction.x * plane.y);
		transformed = (t_dvec2){
			inv_det * (direction.y * pos.x - direction.x * pos.y),
			inv_det * (-plane.y * pos.x + plane.x * pos.y)
		};

		if (transformed.y <= 0) {
			i++;
			continue;
		}

		x = (int)((SCREEN_W / 2.0) * (1 + transformed.x / transformed.y));
		height = abs((int)(SCREEN_H / transformed.y)) * 1.7;

		draw_y.x = -height / 2 + SCREEN_H / 2;
		if (draw_y.x < 0)
			draw_y.x = 0;
		draw_y.y = height / 2 + SCREEN_H / 2;
		if (draw_y.y >= SCREEN_H)
			draw_y.y = SCREEN_H - 1;

		width = abs((int)(SCREEN_W / transformed.y)) *1.2;
		draw_x.x = -width / 2 + x;
		if (draw_x.x < 0)
			draw_x.x = 0;
		draw_x.y = width / 2 + x;
		if (draw_x.y >= SCREEN_W)
			draw_x.y = SCREEN_W - 1;
		j = draw_x.x;
		while (j < draw_x.y)
		{
			texture_pos.x = (int)(256 * (j - (-width / 2 + x)) * texture->width / width) / 256;
			k = draw_y.x;
			if(transformed.y > 0 && j > 0 && j < SCREEN_W && transformed.y* TILESIZE < cub3d->z_buffer[j])
				while (k < draw_y.y)
				{
					d = (k) * 256 - SCREEN_H * 128 + height * 128;
					texture_pos.y = ((d * texture->height) / height) / 256;
					put_pixel_to_buffer(cub3d->rendering_buffer, (t_uvec2){j, k}, get_pixel_color(texture, texture_pos));
					k++;
				}
			j++;
		}
		i++;
	}
}

