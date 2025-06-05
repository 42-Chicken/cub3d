/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_hydrant.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/05 08:59:04 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_textures(t_entity *money)
{
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT] = TEXTURE_ENTITY_FIRE_HYDRANT;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_RIGHT] = TEXTURE_ENTITY_FIRE_HYDRANT;
	money->textures[CUB3D_ENTITY_TEXTURE_RIGHT] = TEXTURE_ENTITY_FIRE_HYDRANT;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_RIGHT] = TEXTURE_ENTITY_FIRE_HYDRANT;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK] = TEXTURE_ENTITY_FIRE_HYDRANT;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_LEFT] = TEXTURE_ENTITY_FIRE_HYDRANT;
	money->textures[CUB3D_ENTITY_TEXTURE_LEFT] = TEXTURE_ENTITY_FIRE_HYDRANT;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_LEFT] = TEXTURE_ENTITY_FIRE_HYDRANT;
}

t_entity	new_fire_hydrant(t_uvec2 pos)
{
	t_entity	fire_hydrant;

	fire_hydrant.in_game = true;
	fire_hydrant.not_displayed = false;
	fire_hydrant.location = (t_dvec2){pos.x + 0.5, pos.y + 0.5};
	setup_textures(&fire_hydrant);
	fire_hydrant.type = CUB3D_ENTITY_FIRE_HYDRANT;
	fire_hydrant.minimap_texture = __TEXTURE_NONE__;
	fire_hydrant.distance_from_floor = -19;
	fire_hydrant.scale = (t_dvec2){0.3, 0.5};
	return (fire_hydrant);
}
