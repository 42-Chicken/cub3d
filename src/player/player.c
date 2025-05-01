/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:27:34 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 10:01:54 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_position_angle(t_cub3d *cub3d, t_dvec2 pos, double angle)
{
	cub3d->player.position = pos;
	cub3d->player.rotation_angle = angle;
}

void	handle_player_movement(t_cub3d *cub3d)
{
	cub3d->player.position.x += cub3d->player.direction.x;
	cub3d->player.position.y += cub3d->player.direction.y;
	cub3d->player.rotation_angle += cub3d->player.rotation_angle_add;
	cub3d->player.cos_r = cos(cub3d->player.rotation_angle);
	cub3d->player.sin_r = sin(cub3d->player.rotation_angle);
	cub3d->player.minimap_pos.x = cub3d->player.position.x * MINIMAP_TILE_SIZE;
	cub3d->player.minimap_pos.y = cub3d->player.position.y * MINIMAP_TILE_SIZE;
	cub3d->player.rotation_angle = fmod(cub3d->player.rotation_angle, 2.0f
			* M_PI);
	if (cub3d->player.rotation_angle < 0)
		cub3d->player.rotation_angle += (2.0f * M_PI);
}
