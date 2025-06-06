/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_baril.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/06 10:08:04 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_textures(t_entity *money)
{
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT] = \
	TEXTURE_ENTITY_FIRE_BARIL;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_RIGHT] = \
	TEXTURE_ENTITY_FIRE_BARIL;
	money->textures[CUB3D_ENTITY_TEXTURE_RIGHT] = \
	TEXTURE_ENTITY_FIRE_BARIL;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_RIGHT] = \
	TEXTURE_ENTITY_FIRE_BARIL;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK] = \
	TEXTURE_ENTITY_FIRE_BARIL;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_LEFT] = \
	TEXTURE_ENTITY_FIRE_BARIL;
	money->textures[CUB3D_ENTITY_TEXTURE_LEFT] = \
	TEXTURE_ENTITY_FIRE_BARIL;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_LEFT] = \
	TEXTURE_ENTITY_FIRE_BARIL;
}

t_entity	new_fire_baril(t_uvec2 pos)
{
	t_entity	fire_baril;

	fire_baril.in_game = true;
	fire_baril.fade = false;
	fire_baril.not_displayed = false;
	fire_baril.location = (t_dvec2){pos.x + 0.5, pos.y + 0.5};
	setup_textures(&fire_baril);
	fire_baril.type = CUB3D_ENTITY_FIRE_BARIL;
	fire_baril.minimap_texture = __TEXTURE_NONE__;
	fire_baril.dst_from_floor = 10;
	fire_baril.scale = (t_dvec2){0.55, 1.5};
	return (fire_baril);
}
