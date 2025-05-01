/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:10:15 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 12:52:55 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_house(t_cub3d *cub3d, t_texture *border, t_texture *house)
{
	t_dvec2		vec_to_spawn;
	t_dvec2		rotated;
	double		len;

	vec_to_spawn = (t_dvec2){
		cub3d->spawn_point.x - cub3d->player.position.x,
		cub3d->spawn_point.y - cub3d->player.position.y
	};
	rotated = (t_dvec2){
		vec_to_spawn.x * cub3d->player.cos_r - \
vec_to_spawn.y * cub3d->player.sin_r,
		vec_to_spawn.x * cub3d->player.sin_r + \
vec_to_spawn.y * cub3d->player.cos_r
	};
	rotated = normalize_vector(rotated);
	len = ft_clamp(sqrt(vec_to_spawn.x * vec_to_spawn.x + vec_to_spawn.y \
		* vec_to_spawn.y), 0, 3.5f);
	igmlx_simple_copy_to_dest_ignore_null(house,
		cub3d->rendering_buffer,
		(t_uvec2){
		cub3d->minimap.border_pos.x + border->width / 2 - house->width / 2
		+ rotated.x * len * MINIMAP_TILE_SIZE,
		cub3d->minimap.border_pos.y + border->height / 2 - house->height / 2
		+ rotated.y * len * MINIMAP_TILE_SIZE,
	});
}

void	render_minimap(t_cub3d *cub3d)
{
	t_texture	*border;
	t_texture	*player;
	t_texture	*north;
	t_texture	*house;

	house = get_texture(cub3d, TEXTURE_MINIMAP_HOUSE);
	border = get_texture(cub3d, TEXTURE_MINIMAP_BORDER);
	north = get_texture(cub3d, TEXTURE_MINIMAP_NORTH_INDICATION);
	player = get_texture(cub3d, TEXTURE_MINIMAP_PLAYER);
	minimap_handle_background(cub3d, border);
	igmlx_simple_copy_to_dest_ignore_null(border, cub3d->rendering_buffer,
		cub3d->minimap.border_pos);
	igmlx_simple_copy_to_dest_ignore_null(player, cub3d->rendering_buffer,
		cub3d->minimap.player_pos);
	igmlx_simple_copy_to_dest_ignore_null(north, cub3d->rendering_buffer,
		(t_uvec2){(border->width / 2 + 5) + cub3d->player.cos_r * border->width
		/ 2, SCREEN_H - (border->height / 2) - (north->height + 5)
		+ cub3d->player.sin_r * border->height / 2});
	handle_house(cub3d, border, house);
}

// draw_line(cub3d->rendering_buffer, 0xFF0000,
// 	(t_vec2){cub3d->minimap.player_pos.x + player->width / 2,
// 	cub3d->minimap.player_pos.y + player->height / 2},
// 	(t_vec2){cub3d->minimap.player_pos.x + player->width / 2
// 	+ cub3d->player.cos_r * 25, cub3d->minimap.player_pos.y + player->height
// 	/ 2 + cub3d->player.sin_r * 25});
