/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/03 14:02:43 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_textures(t_entity *money)
{
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_RIGHT] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_RIGHT] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_RIGHT] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_LEFT] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_LEFT] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_LEFT] = TEXTURE_ENTITY_BULLET;
}

void	update_bullet(t_cub3d *cub3d, t_entity *entity)
{
	if (map_is_wall(cub3d, entity->location.x, entity->location.y) || entity->distance_from_player > 60)
	{
		entity->in_game = false;
		return ;
	}
	entity->location.x += cos(entity->rotation_angle) * 3;
	entity->location.y += sin(entity->rotation_angle) * 3;
}

t_entity	new_bullet(t_dvec2 pos)
{
	t_entity	bullet;

	bullet.in_game = true;
	bullet.not_displayed = false;
	bullet.location = (t_dvec2){pos.x, pos.y};
	setup_textures(&bullet);
	bullet.type = CUB3D_ENTITY_BULLET;
	bullet.minimap_texture = __TEXTURE_NONE__;
	bullet.distance_from_floor = -5;
	bullet.scale = (t_dvec2){0.07, 0.07};
	return (bullet);
}
