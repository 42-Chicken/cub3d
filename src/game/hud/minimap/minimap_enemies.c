/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_enemies.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:08:39 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 08:52:46 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	minimap_draw_entity(t_cub3d *cub3d, t_entity *entity,
	t_texture *border, t_texture *texture)
{
	t_dvec2		vec_to_spawn;
	t_dvec2		rotated;
	double		len;

	vec_to_spawn = (t_dvec2){
		entity->location.x - cub3d->player.location.x,
		entity->location.y - cub3d->player.location.y
	};
	rotated = (t_dvec2){
		vec_to_spawn.x * -cub3d->player.sin_r - \
vec_to_spawn.y * -cub3d->player.cos_r,
		vec_to_spawn.x * -cub3d->player.cos_r + \
vec_to_spawn.y * -cub3d->player.sin_r
	};
	rotated = normalize_vector(rotated);
	len = ft_clamp(sqrt(vec_to_spawn.x * vec_to_spawn.x + vec_to_spawn.y \
		* vec_to_spawn.y), 0, 3.5f);
	igmlx_simple_copy_to_dest(texture,
		cub3d->rendering_buffer,
		(t_uvec2){
		cub3d->minimap.border_pos.x + border->width / 2 - texture->width / 2
		+ rotated.x * len * MINIMAP_TILE_SIZE,
		cub3d->minimap.border_pos.y + border->height / 2 - texture->height / 2
		+ rotated.y * len * MINIMAP_TILE_SIZE,
	});
}

void	minimap_handle_enemies(t_cub3d *cub3d, t_texture *border)
{
	size_t	i;

	i = 0;
	while (i < cub3d->entity_count)
	{
		if (cub3d->entities[i].in_game)
			minimap_draw_entity(cub3d, &cub3d->entities[i], border, \
				get_texture(cub3d, cub3d->entities[i].minimap_texture));
		i++;
	}
}
