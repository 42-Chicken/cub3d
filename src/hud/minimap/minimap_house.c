/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_house.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:08:39 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 09:49:23 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_house(t_cub3d *cub3d, t_texture *border, t_texture *house)
{
	t_dvec2		vec_to_spawn;
	t_dvec2		rotated;
	double		len;

	vec_to_spawn = (t_dvec2){
		cub3d->spawn_point.x + 0.5 - cub3d->player.position.x,
		cub3d->spawn_point.y + 0.5 - cub3d->player.position.y
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
	igmlx_simple_copy_to_dest(house,
		cub3d->rendering_buffer,
		(t_uvec2){
		cub3d->minimap.border_pos.x + border->width / 2 - house->width / 2
		+ rotated.x * len * MINIMAP_TILE_SIZE,
		cub3d->minimap.border_pos.y + border->height / 2 - house->height / 2
		+ rotated.y * len * MINIMAP_TILE_SIZE,
	});
}
