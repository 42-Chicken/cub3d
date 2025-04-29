/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:10:15 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/29 15:24:21 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_background(t_cub3d *cub3d, t_texture *border)
{
	size_t	x;
	size_t	y;
	t_color	color;

	y = (size_t)cub3d->player.position.y - (MINIMAP_TILE_SIZE / 4) + 1;
	while (y < (size_t)cub3d->player.position.y + (MINIMAP_TILE_SIZE / 4))
	{
		x = (size_t)cub3d->player.position.x - (MINIMAP_TILE_SIZE / 4 ) + 1;
		while (x < (size_t)cub3d->player.position.x + (MINIMAP_TILE_SIZE / 4))
		{
			if (map_is_floor(cub3d, x, y))
				color = 0xFF0000;
			else if (map_is_void(cub3d, x, y))
				color = 0x0000FF;
			else
				color = 0x00FF00;
			if (x == (size_t)cub3d->player.position.x
				&& y == (size_t)cub3d->player.position.y)
				color = 0xFF00FF;
			draw_rect(cub3d->rendering_buffer, color,
				(t_uvec2){
					(cub3d->minimap.border_pos.x + border->width / 2 + ((x - (size_t)cub3d->player.position.x)) * MINIMAP_TILE_SIZE) - MINIMAP_TILE_SIZE / 2 + 1,
					(cub3d->minimap.border_pos.y + border->height / 2 + ((y - (size_t)cub3d->player.position.y)) * MINIMAP_TILE_SIZE) - MINIMAP_TILE_SIZE / 2 + 1
				},
				(t_uvec2){
					(cub3d->minimap.border_pos.x + border->width / 2 + ((x - (size_t)cub3d->player.position.x)) * MINIMAP_TILE_SIZE) + MINIMAP_TILE_SIZE / 2 + 1,
					(cub3d->minimap.border_pos.y + border->height / 2 + ((y - (size_t)cub3d->player.position.y)) * MINIMAP_TILE_SIZE) + MINIMAP_TILE_SIZE / 2 + 1
				});
			x++;
		}
		y++;
	}
}

void	render_minimap(t_cub3d *cub3d)
{
	t_texture	*border;
	t_texture	*north;

	// t_texture	*minimap;
	// minimap = get_texture(cub3d, TEXTURE_MINIMAP);
	border = get_texture(cub3d, TEXTURE_MINIMAP_BORDER);
	north = get_texture(cub3d, TEXTURE_MINIMAP_NORTH_INDICATION);
	draw_background(cub3d, border);
	// igmlx_simple_copy_to_dest_ignore_null(minimap, cub3d->rendering_buffer,
	// 	(t_uvec2){cub3d->minimap.border_pos.x - (int)cub3d->player.position.x
	// 	* MINIMAP_TILE_SIZE + border->width / 2 - MINIMAP_TILE_SIZE / 2,
	// 	cub3d->minimap.border_pos.y - (int)cub3d->player.position.y
	// 	* MINIMAP_TILE_SIZE + border->height / 2 - MINIMAP_TILE_SIZE / 2});
	igmlx_simple_copy_to_dest_ignore_null(border, cub3d->rendering_buffer,
		cub3d->minimap.border_pos);
	// igmlx_simple_copy_to_dest_ignore_null(north, cub3d->rendering_buffer,
	// (t_uvec2){
	// 	border->width / 2 - north->width / 2 + MINIMAP_OFFSET, SCREEN_H
	// - border->height - north->height / 2 - MINIMAP_OFFSET
	// });
	cub3d->player.rotation_angle += 0.05f;
	if (cub3d->player.rotation_angle > 180)
		cub3d->player.rotation_angle = 0;
	igmlx_simple_copy_to_dest_ignore_null(north, cub3d->rendering_buffer,
		(t_uvec2){(border->width / 2 + 5) + cos(cub3d->player.rotation_angle)
		* border->width / 2, SCREEN_H - (border->height / 2) - (north->height
			+ 5) + -sin(cub3d->player.rotation_angle) * border->height / 2});
}
