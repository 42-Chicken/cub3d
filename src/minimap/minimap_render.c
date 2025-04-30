/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:10:15 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/30 13:06:59 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool find_black_pixel_before_and_after(t_cub3d *cub3d, int x, int y)
{
	t_texture *border;

	border = get_texture(cub3d, TEXTURE_MINIMAP_BORDER);
	x -= cub3d->minimap.border_pos.x;
	y -= cub3d->minimap.border_pos.y;
	if (y > border->height - 5)
		return (false);
	while (x > 0 && *get_pixel(border, (t_uvec2){x, y}) != 0x000000)
		x--;
	if (*get_pixel(border, (t_uvec2){x, y}) != 0x000000)
		return (false);
	x++;
	while (x < border->width && *get_pixel(border, (t_uvec2){x, y}) != 0x000000)
		x++;
	if (*get_pixel(border, (t_uvec2){x, y}) != 0x000000)
		return (false);
	return (true);
}

double clamp(double d, double min, double max) {
	const double t = d < min ? min : d;
	return t > max ? max : t;
}

void	draw_background(t_cub3d *cub3d, t_texture *border)
{
	t_texture	*minimap = get_texture(cub3d, TEXTURE_MINIMAP);
	int			mid_screen_x;
	int			mid_screen_y;
	float		rel_x;
	float		rel_y;
	float		rot_x;
	float		rot_y;
	int			tex_x;
	int			tex_y;

	(void)border;
	float angle = cub3d->player.rotation_angle; // rotation in radians (e.g. 0.5 = ~28 degrees)
    mid_screen_x = SCREEN_W / 2;// (cub3d->minimap.border_pos.x) + border->width / 2;
    mid_screen_y = SCREEN_H / 4;// (cub3d->minimap.border_pos.y) + border->height / 2;
	// for (int y = cub3d->minimap.border_pos.y; y < (int)cub3d->minimap.border_pos.y + border->height; y++)
	// {
	// 	for (int x = cub3d->minimap.border_pos.x; x < (int)cub3d->minimap.border_pos.x + border->width; x++)
	// 	{
	for (int y = 0; y < SCREEN_H; y++)
	{
		for (int x = 0; x < SCREEN_W; x++)
		{
			// Map screen to texture space (linearly)
			float tex_coord_x = (float)(x) * minimap->width / SCREEN_W;
			float tex_coord_y = (float)(y ) * minimap->height / (SCREEN_H / 2);

			// Rotate around texture point (10, 10)
			rel_x = tex_coord_x - (cub3d->player.position.x * MINIMAP_TILE_SIZE);
			rel_y = tex_coord_y - (cub3d->player.position.y * MINIMAP_TILE_SIZE);

			rot_x = cosf(angle) * rel_x - sinf(angle) * rel_y + (cub3d->player.position.x * MINIMAP_TILE_SIZE);
			rot_y = sinf(angle) * rel_x + cosf(angle) * rel_y + (cub3d->player.position.y * MINIMAP_TILE_SIZE);

			// Wrap or clamp
			tex_x = ((int)rot_x + minimap->width) % minimap->width;
			tex_y = ((int)rot_y + minimap->height) % minimap->height;

			// Draw the pixel
			put_pixel_to_buffer(cub3d->rendering_buffer, (t_uvec2){x, y},
				*get_pixel(minimap, (t_uvec2){tex_x, tex_y}));
		}
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
	// (t_uvec2){0, 0});
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
	// cub3d->player.rotation_angle += 0.05f;
	// if (cub3d->player.rotation_angle > 180)
	// 	cub3d->player.rotation_angle = 0;
	igmlx_simple_copy_to_dest_ignore_null(north, cub3d->rendering_buffer,
		(t_uvec2){(border->width / 2 + 5) + cos(cub3d->player.rotation_angle)
		* border->width / 2, SCREEN_H - (border->height / 2) - (north->height
			+ 5) + -sin(cub3d->player.rotation_angle) * border->height / 2});
}
