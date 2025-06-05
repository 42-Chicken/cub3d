/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/05 10:23:01 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_textures(t_entity *money)
{
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT] = TEXTURE_ENTITY_RAT;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_RIGHT] = TEXTURE_ENTITY_RAT;
	money->textures[CUB3D_ENTITY_TEXTURE_RIGHT] = TEXTURE_ENTITY_RAT;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_RIGHT] = TEXTURE_ENTITY_RAT;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK] = TEXTURE_ENTITY_RAT;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_LEFT] = TEXTURE_ENTITY_RAT;
	money->textures[CUB3D_ENTITY_TEXTURE_LEFT] = TEXTURE_ENTITY_RAT;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_LEFT] = TEXTURE_ENTITY_RAT;
}

t_entity	new_rat(t_uvec2 pos)
{
	t_entity	rat;

	rat.in_game = true;
	rat.not_displayed = false;
	rat.location = (t_dvec2){pos.x + 0.5, pos.y + 0.5};
	setup_textures(&rat);
	rat.type = CUB3D_ENTITY_RAT;
	rat.minimap_texture = __TEXTURE_NONE__;
	rat.distance_from_floor = -25;
	rat.scale = (t_dvec2){0.35, 0.25};
	return (rat);
}
