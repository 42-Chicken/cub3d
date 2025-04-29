/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:10:15 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/29 15:39:02 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_background(t_cub3d *cub3d, t_texture *border)
{
	size_t	x;
	size_t	y;

	size_t	x1;
	size_t	y1;
	t_color	color;

	y = cub3d->minimap.border_pos.y;
	y1 = (size_t)cub3d->player.position.y - 4;
	while (y < (size_t)border->height + cub3d->minimap.border_pos.y)
	{
		x = cub3d->minimap.border_pos.x;
		x1 = (size_t)cub3d->player.position.x - 4;
		while (x < (size_t)border->width + cub3d->minimap.border_pos.x)
		{
			if (map_is_floor(cub3d, (x - border->width), y - cub3d->minimap.border_pos.y))
				color = 0xFF0000;
			else if (map_is_void(cub3d, (x - border->width), y - cub3d->minimap.border_pos.y))
				color = 0x0000FF;
			else
				color = 0x00FF00;
			if (x1 == (size_t)cub3d->player.position.x
				&& y1 == (size_t)cub3d->player.position.y)
				color = 0xFF00FF;
			put_pixel_to_buffer(cub3d->rendering_buffer, (t_uvec2){x, y}, color);
			x++;
			x1++;
		}
		y++;
		y1++;
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
