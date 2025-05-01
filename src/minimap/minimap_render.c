/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:10:15 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 09:32:29 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	find_black_pixel_before_and_after(t_cub3d *cub3d, int x, int y)
{
	t_texture	*border;

	border = get_texture(cub3d, TEXTURE_MINIMAP_BORDER);
	x -= cub3d->minimap.border_pos.x;
	y -= cub3d->minimap.border_pos.y;
	if (y > border->height - 5 || y < 5)
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

void	draw_background(t_cub3d *cub3d, t_texture *border)
{
	t_texture	*minimap;
	int y;
	int x;

	(void)border;

	minimap = get_texture(cub3d, TEXTURE_MINIMAP);
	float	cos_a = cos(cub3d->player.rotation_angle);
	float	sin_a = sin(cub3d->player.rotation_angle);

	t_dvec2 player_minimap_pos;
	player_minimap_pos = (t_dvec2){
		cub3d->player.position.x * MINIMAP_TILE_SIZE,
		cub3d->player.position.y * MINIMAP_TILE_SIZE,
	};
	t_dvec2 offset;
	offset = (t_dvec2){
		-player_minimap_pos.x + cub3d->minimap.border_pos.x + border->width / 2,
		-player_minimap_pos.y + cub3d->minimap.border_pos.y + border->height / 2,
	};

	t_dvec2 direction;
	t_dvec2 rotated;

	double circle_rayon = 95; // px
	t_vec2	center;
	center = (t_vec2){
		cub3d->minimap.border_pos.x + border->width / 2,
		cub3d->minimap.border_pos.y + border->height / 2,
	};

	y = player_minimap_pos.y - 4 * MINIMAP_TILE_SIZE;
	while (y < player_minimap_pos.y + 4 * MINIMAP_TILE_SIZE)
	{
		x = player_minimap_pos.x - 4 * MINIMAP_TILE_SIZE;;
		while (x < player_minimap_pos.x + 4 * MINIMAP_TILE_SIZE)
		{
			if (!(pow((x + offset.x)- center.x, 2) + pow((y + offset.y) - center.y, 2) < circle_rayon * circle_rayon))
			{
				x++;
				continue;
			}
			direction.x = x - player_minimap_pos.x;
			direction.y = y - player_minimap_pos.y;

			rotated.x = direction.x * cos_a + direction.y * sin_a + player_minimap_pos.x;
			rotated.y = -direction.x * sin_a + direction.y * cos_a + player_minimap_pos.y;

			put_pixel_to_buffer(cub3d->rendering_buffer,
				(t_uvec2){x + offset.x, y + offset.y}, get_pixel_color(minimap, (t_uvec2){(int)rotated.x, (int)rotated.y}));
			x++;
		}
		y++;
	}
}

void	render_minimap(t_cub3d *cub3d)
{
	t_texture	*border;
	t_texture	*player;
	t_texture	*north;

	// t_texture	*minimap;
	// minimap = get_texture(cub3d, TEXTURE_MINIMAP);
	border = get_texture(cub3d, TEXTURE_MINIMAP_BORDER);
	north = get_texture(cub3d, TEXTURE_MINIMAP_NORTH_INDICATION);
	player = get_texture(cub3d, TEXTURE_MINIMAP_PLAYER);
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
	igmlx_simple_copy_to_dest_ignore_null(player, cub3d->rendering_buffer,
		cub3d->minimap.player_pos);
	// igmlx_simple_copy_to_dest_ignore_null(north, cub3d->rendering_buffer,
	// (t_uvec2){
	// 	border->width / 2 - north->width / 2 + MINIMAP_OFFSET, SCREEN_H
	// - border->height - north->height / 2 - MINIMAP_OFFSET
	// });
	// cub3d->player.rotation_angle += 0.05f;
	// if (cub3d->player.rotation_angle > 180)
	// 	cub3d->player.rotation_angle = 0;
	draw_line(cub3d->rendering_buffer, 0xFF0000,
		(t_vec2){cub3d->minimap.player_pos.x + player->width / 2,
		cub3d->minimap.player_pos.y + player->height / 2},
		(t_vec2){cub3d->minimap.player_pos.x + player->width / 2
		+ cos(cub3d->player.rotation_angle) * 25, cub3d->minimap.player_pos.y
		+ player->height / 2 + sin(cub3d->player.rotation_angle) * 25});
	igmlx_simple_copy_to_dest_ignore_null(north, cub3d->rendering_buffer,
		(t_uvec2){(border->width / 2 + 5) + cos(cub3d->player.rotation_angle)
		* border->width / 2, SCREEN_H - (border->height / 2) - (north->height
			+ 5) + sin(cub3d->player.rotation_angle) * border->height / 2});
}
