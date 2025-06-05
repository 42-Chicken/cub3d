/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trashcan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/05 11:14:35 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_textures(t_entity *trashcan)
{
	trashcan->textures[CUB3D_ENTITY_TEXTURE_FRONT] = TEXTURE_ENTITY_TRASHCAN;
	trashcan->textures[CUB3D_ENTITY_TEXTURE_FRONT_RIGHT] = TEXTURE_ENTITY_TRASHCAN;
	trashcan->textures[CUB3D_ENTITY_TEXTURE_RIGHT] = TEXTURE_ENTITY_TRASHCAN;
	trashcan->textures[CUB3D_ENTITY_TEXTURE_BACK_RIGHT] = TEXTURE_ENTITY_TRASHCAN;
	trashcan->textures[CUB3D_ENTITY_TEXTURE_BACK] = TEXTURE_ENTITY_TRASHCAN;
	trashcan->textures[CUB3D_ENTITY_TEXTURE_BACK_LEFT] = TEXTURE_ENTITY_TRASHCAN;
	trashcan->textures[CUB3D_ENTITY_TEXTURE_LEFT] = TEXTURE_ENTITY_TRASHCAN;
	trashcan->textures[CUB3D_ENTITY_TEXTURE_FRONT_LEFT] = TEXTURE_ENTITY_TRASHCAN;
}

t_entity	new_trashcan(t_uvec2 pos)
{
	t_entity	trashcan;

	trashcan.in_game = true;
	trashcan.fade = true;
	trashcan.location = (t_dvec2){pos.x + 0.5, pos.y + 0.5};
	setup_textures(&trashcan);
	trashcan.type = CUB3D_ENTITY_TRASHCAN;
	trashcan.minimap_texture = __TEXTURE_NONE__;
	trashcan.rotation_angle = M_PI / 2;
	trashcan.distance_from_floor = -18;
	trashcan.scale = (t_dvec2){0.4, 0.5};
	return (trashcan);
}
