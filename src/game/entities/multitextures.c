/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multitextures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:28:36 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/22 14:41:42 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	normalizeangle2(double angle)
{
	while (angle < 0)
		angle += (2.0 * M_PI);
	while (angle >= (2.0 * M_PI))
		angle -= (2.0 * M_PI);
	return (angle);
}

t_texture	*get_entity_texture(t_cub3d *cub3d, t_entity *entity)
{
	t_e_cub3d_entity_textures_rotations	rotation;
	double								diff;

	diff = normalizeangle2(entity->rotation_angle
			- cub3d->player.rotation_angle);
	if ((diff >= 0 && diff < M_PI / 8) || (diff >= 15 * M_PI / 8
			&& diff < (2.0 * M_PI)))
		rotation = CUB3D_ENTITY_TEXTURE_FRONT;
	else if (diff >= M_PI / 8 && diff < 3 * M_PI / 8)
		rotation = CUB3D_ENTITY_TEXTURE_FRONT_RIGHT;
	else if (diff >= 3 * M_PI / 8 && diff < 5 * M_PI / 8)
		rotation = CUB3D_ENTITY_TEXTURE_RIGHT;
	else if (diff >= 5 * M_PI / 8 && diff < 7 * M_PI / 8)
		rotation = CUB3D_ENTITY_TEXTURE_BACK_RIGHT;
	else if (diff >= 7 * M_PI / 8 && diff < 9 * M_PI / 8)
		rotation = CUB3D_ENTITY_TEXTURE_BACK;
	else if (diff >= 9 * M_PI / 8 && diff < 11 * M_PI / 8)
		rotation = CUB3D_ENTITY_TEXTURE_BACK_LEFT;
	else if (diff >= 11 * M_PI / 8 && diff < 13 * M_PI / 8)
		rotation = CUB3D_ENTITY_TEXTURE_LEFT;
	else
		rotation = CUB3D_ENTITY_TEXTURE_FRONT_LEFT;
	return (get_texture(cub3d, entity->textures[rotation]));
}
