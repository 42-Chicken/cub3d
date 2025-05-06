/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:27:34 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 14:56:00 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_position_angle(t_cub3d *cub3d, t_dvec2 pos, double angle)
{
	cub3d->player.location = pos;
	cub3d->player.rotation_angle = angle;
}

void	handle_player_movements(t_cub3d *cub3d)
{
	double	multiplier;

	multiplier = 0;
	if (is_pressed(cub3d, 'w'))
		multiplier += 1;
	if (is_pressed(cub3d, 's'))
		multiplier -= 1;
	cub3d->player.location.x += cub3d->player.cos_r * multiplier
		* ((double)cub3d->settings.player_speed / 10);
	cub3d->player.location.y += cub3d->player.sin_r * multiplier
		* ((double)cub3d->settings.player_speed / 10);
}

void	handle_player_rotation(t_cub3d *cub3d)
{
	if (is_pressed(cub3d, 'd'))
		cub3d->player.rotation_angle
			+= ((double)cub3d->settings.player_rotation_speed / 100);
	if (is_pressed(cub3d, 'a'))
		cub3d->player.rotation_angle
			-= ((double)cub3d->settings.player_rotation_speed / 100);
	cub3d->player.cos_r = cos(cub3d->player.rotation_angle);
	cub3d->player.sin_r = sin(cub3d->player.rotation_angle);
	cub3d->player.rotation_angle = fmod(cub3d->player.rotation_angle, 2.0f
			* M_PI);
	if (cub3d->player.rotation_angle < 0)
		cub3d->player.rotation_angle += (2.0f * M_PI);
	if (cub3d->player.money > MAX_MONEY)
		cub3d->player.money = MAX_MONEY;
}

void	update_player(t_cub3d *cub3d)
{
	handle_player_movements(cub3d);
	handle_player_rotation(cub3d);
	cub3d->player.minimap_pos.x = cub3d->player.location.x * MINIMAP_TILE_SIZE
		+ MINIMAP_TILE_SIZE / 2;
	cub3d->player.minimap_pos.y = cub3d->player.location.y * MINIMAP_TILE_SIZE
		+ MINIMAP_TILE_SIZE / 2;
}
