/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   money.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 10:52:41 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_textures(t_entity *money)
{
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT] = TEXTURE_ENTITY_MONEY;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_RIGHT] = TEXTURE_ENTITY_MONEY;
	money->textures[CUB3D_ENTITY_TEXTURE_RIGHT] = TEXTURE_ENTITY_MONEY;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_RIGHT] = TEXTURE_ENTITY_MONEY;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK] = TEXTURE_ENTITY_MONEY;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_LEFT] = TEXTURE_ENTITY_MONEY;
	money->textures[CUB3D_ENTITY_TEXTURE_LEFT] = TEXTURE_ENTITY_MONEY;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_LEFT] = TEXTURE_ENTITY_MONEY;
}

void	update_money(t_cub3d *cub3d, t_entity *entity)
{
	if (!entity->flag)
	{
		entity->distance_from_floor += 0.05;
		if (entity->distance_from_floor > -23)
			entity->flag = true;
	}
	else
	{
		entity->distance_from_floor -= 0.05;
		if (entity->distance_from_floor <= -25)
			entity->flag = false;
	}
	if (entity->distance_from_player <= 0.5)
	{
		entity->in_game = false;
		cub3d->player.money += 10;
	}
}

t_entity	new_money(t_uvec2 pos)
{
	t_entity	money;

	money.health = 10;
	money.location = (t_dvec2){pos.x + 0.5, pos.y + 0.5};
	setup_textures(&money);
	money.type = CUB3D_ENTITY_MONEY;
	money.in_game = true;
	money.minimap_texture = TEXTURE_MINIMAP_MONEY;
	money.rotation_angle = M_PI / 2;
	money.scale = (t_dvec2){
		0.2,
		0.2,
	};
	money.distance_from_floor = -25;
	return (money);
}
