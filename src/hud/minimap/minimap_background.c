/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:23:19 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 10:38:56 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define RADIUS MINIMAP_BACKGROUND_CIRCLE_RADIUS

static t_dvec2	get_rotated(t_cub3d *cub3d, t_vec2 c)
{
	t_dvec2	direction;
	t_dvec2	rotated;

	direction.x = c.x - cub3d->player.minimap_pos.x;
	direction.y = c.y - cub3d->player.minimap_pos.y;
	rotated.x = direction.x * cub3d->player.cos_r + direction.y
		* cub3d->player.sin_r + cub3d->player.minimap_pos.x;
	rotated.y = -direction.x * cub3d->player.sin_r + direction.y
		* cub3d->player.cos_r + cub3d->player.minimap_pos.y;
	return (rotated);
}

static bool	is_in_circle(t_vec2 c, t_vec2 offset, t_vec2 center)
{
	int	dx;
	int	dy;

	dx = (c.x + offset.x) - center.x;
	dy = (c.y + offset.y) - center.y;
	return (!(dx * dx + dy * dy < RADIUS * RADIUS));
}

static void	minimap_draw_background(t_cub3d *cub3d, t_vec2 offset,
		t_vec2 center)
{
	t_texture	*minimap;
	t_vec2		c;
	t_dvec2		rotated;

	minimap = get_texture(cub3d, __TEXTURE_MINIMAP__);
	c.y = cub3d->player.minimap_pos.y - 4 * MINIMAP_TILE_SIZE;
	while (c.y < cub3d->player.minimap_pos.y + 4 * MINIMAP_TILE_SIZE)
	{
		c.x = cub3d->player.minimap_pos.x - 4 * MINIMAP_TILE_SIZE;
		while (c.x < cub3d->player.minimap_pos.x + 4 * MINIMAP_TILE_SIZE)
		{
			if (is_in_circle(c, offset, center))
			{
				c.x++;
				continue ;
			}
			rotated = get_rotated(cub3d, c);
			put_pixel_to_buffer(cub3d->rendering_buffer, (t_uvec2){c.x
				+ offset.x, c.y + offset.y}, get_pixel_color(minimap,
					(t_uvec2){(int)rotated.x, (int)rotated.y}));
			c.x++;
		}
		c.y++;
	}
}

void	minimap_handle_background(t_cub3d *cub3d, t_texture *border)
{
	t_vec2	minimap_background_offset;
	t_vec2	center;

	center = (t_vec2){
		cub3d->minimap.border_pos.x + border->width / 2,
		cub3d->minimap.border_pos.y + border->height / 2,
	};
	minimap_background_offset = (t_vec2){
		-cub3d->player.minimap_pos.x + cub3d->minimap.border_pos.x
		+ border->width / 2,
		-cub3d->player.minimap_pos.y + cub3d->minimap.border_pos.y
		+ border->height / 2,
	};
	minimap_draw_background(cub3d, minimap_background_offset, center);
}
