/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soldier.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/22 14:46:36 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_textures(t_entity *soldier)
{
	soldier->textures[CUB3D_ENTITY_TEXTURE_FRONT] = \
	TEXTURE_ENTITY_SOLDIER_FRONT;
	soldier->textures[CUB3D_ENTITY_TEXTURE_FRONT_RIGHT] = \
	TEXTURE_ENTITY_SOLDIER_FRONT_RIGHT;
	soldier->textures[CUB3D_ENTITY_TEXTURE_RIGHT] = \
	TEXTURE_ENTITY_SOLDIER_RIGHT;
	soldier->textures[CUB3D_ENTITY_TEXTURE_BACK_RIGHT] = \
	TEXTURE_ENTITY_SOLDIER_BACK_RIGHT;
	soldier->textures[CUB3D_ENTITY_TEXTURE_BACK] = \
	TEXTURE_ENTITY_SOLDIER_BACK;
	soldier->textures[CUB3D_ENTITY_TEXTURE_BACK_LEFT] = \
	TEXTURE_ENTITY_SOLDIER_BACK_LEFT;
	soldier->textures[CUB3D_ENTITY_TEXTURE_LEFT] = \
	TEXTURE_ENTITY_SOLDIER_LEFT;
	soldier->textures[CUB3D_ENTITY_TEXTURE_FRONT_LEFT] = \
	TEXTURE_ENTITY_SOLDIER_FRONT_LEFT;
}

t_entity	new_soldier(t_uvec2 pos)
{
	t_entity	soldier;

	soldier.health = 10;
	soldier.location = (t_dvec2){pos.x + 0.5, pos.y + 0.5};
	setup_textures(&soldier);
	soldier.type = CUB3D_ENTITY_OFFICER;
	soldier.in_game = true;
	soldier.minimap_texture = TEXTURE_MINIMAP_ENEMY;
	soldier.rotation_angle = M_PI / 2;
	soldier.scale = (t_dvec2){
		1.2,
		1.3,
	};
	soldier.distance_from_floor = 0;
	return (soldier);
}
