/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lamp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/03 15:14:39 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_textures(t_entity *money)
{
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT] = TEXTURE_ENTITY_LAMP;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_RIGHT] = TEXTURE_ENTITY_LAMP;
	money->textures[CUB3D_ENTITY_TEXTURE_RIGHT] = TEXTURE_ENTITY_LAMP;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_RIGHT] = TEXTURE_ENTITY_LAMP;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK] = TEXTURE_ENTITY_LAMP;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_LEFT] = TEXTURE_ENTITY_LAMP;
	money->textures[CUB3D_ENTITY_TEXTURE_LEFT] = TEXTURE_ENTITY_LAMP;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_LEFT] = TEXTURE_ENTITY_LAMP;
}

t_entity	new_lamp(t_uvec2 pos)
{
	t_entity	lamp;

	lamp.in_game = true;
	lamp.not_displayed = false;
	lamp.location = (t_dvec2){pos.x + 0.5, pos.y + 0.5};
	setup_textures(&lamp);
	lamp.type = CUB3D_ENTITY_LAMP;
	lamp.minimap_texture = __TEXTURE_NONE__;
	lamp.distance_from_floor = 55;
	lamp.scale = (t_dvec2){0.5, 3};
	return (lamp);
}
