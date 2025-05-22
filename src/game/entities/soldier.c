/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soldier.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/22 12:03:08 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_entity	new_soldier(t_uvec2 pos)
{
	t_entity	soldier;

	soldier.health = 10;
	soldier.location = (t_dvec2){pos.x + 0.5, pos.y + 0.5};
	soldier.textures[0] = TEXTURE_ENTITY_GUARD;
	soldier.type = CUB3D_ENTITY_OFFICER;
	soldier.in_game = true;
	soldier.scale = (t_dvec2){
		1.2,
		1.7,
	};
	soldier.distance_from_floor = 160;
	return (soldier);
}
