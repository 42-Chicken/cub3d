/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/05 11:03:29 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_textures(t_entity *money)
{
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT] = TEXTURE_ENTITY_TREE2;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_RIGHT] = TEXTURE_ENTITY_TREE2;
	money->textures[CUB3D_ENTITY_TEXTURE_RIGHT] = TEXTURE_ENTITY_TREE2;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_RIGHT] = TEXTURE_ENTITY_TREE2;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK] = TEXTURE_ENTITY_TREE2;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_LEFT] = TEXTURE_ENTITY_TREE2;
	money->textures[CUB3D_ENTITY_TEXTURE_LEFT] = TEXTURE_ENTITY_TREE2;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_LEFT] = TEXTURE_ENTITY_TREE2;
}

t_entity	new_tree2(t_uvec2 pos)
{
	t_entity	tree;

	tree.in_game = true;
	tree.fade = true;
	tree.not_displayed = false;
	tree.location = (t_dvec2){pos.x + 0.5, pos.y + 0.5};
	setup_textures(&tree);
	tree.type = CUB3D_ENTITY_TREE2;
	tree.minimap_texture = __TEXTURE_NONE__;
	tree.distance_from_floor = 65;
	tree.scale = (t_dvec2){2.5, 3.5};
	return (tree);
}
