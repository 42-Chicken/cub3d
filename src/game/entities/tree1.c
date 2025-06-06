/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/06 10:07:37 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_textures(t_entity *money)
{
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT] = TEXTURE_ENTITY_TREE1;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_RIGHT] = TEXTURE_ENTITY_TREE1;
	money->textures[CUB3D_ENTITY_TEXTURE_RIGHT] = TEXTURE_ENTITY_TREE1;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_RIGHT] = TEXTURE_ENTITY_TREE1;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK] = TEXTURE_ENTITY_TREE1;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_LEFT] = TEXTURE_ENTITY_TREE1;
	money->textures[CUB3D_ENTITY_TEXTURE_LEFT] = TEXTURE_ENTITY_TREE1;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_LEFT] = TEXTURE_ENTITY_TREE1;
}

t_entity	new_tree1(t_uvec2 pos)
{
	t_entity	tree;

	tree.in_game = true;
	tree.fade = true;
	tree.not_displayed = false;
	tree.location = (t_dvec2){pos.x + 0.5, pos.y + 0.5};
	setup_textures(&tree);
	tree.type = CUB3D_ENTITY_TREE1;
	tree.minimap_texture = __TEXTURE_NONE__;
	tree.dst_from_floor = 35;
	tree.scale = (t_dvec2){1.5, 2.5};
	return (tree);
}
