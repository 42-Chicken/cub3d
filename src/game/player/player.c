/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:27:34 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 10:40:04 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_position_angle(t_cub3d *cub3d, t_dvec2 pos, double angle)
{
	cub3d->player.location = pos;
	cub3d->player.rotation_angle = angle;
}

static bool	can_move(t_cub3d *cub3d, double x, double y, double r)
{
	double	left;
	double	right;
	double	top;
	double	bottom;

	left = x - r;
	right = x + r;
	top = y - r;
	bottom = y + r;
	if (map_is_wall(cub3d, (size_t)floor(left), (size_t)floor(top)))
		return (false);
	if (map_is_wall(cub3d, (size_t)floor(right), (size_t)floor(top)))
		return (false);
	if (map_is_wall(cub3d, (size_t)floor(right), (size_t)floor(bottom)))
		return (false);
	if (map_is_wall(cub3d, (size_t)floor(left), (size_t)floor(bottom)))
		return (false);
	return (true);
}

void	handle_player_movements(t_cub3d *cub3d)
{
	double	mult;
	double	dx;
	double	dy;

	mult = 0;
	if (is_pressed(cub3d, 'w'))
		mult += 1;
	if (is_pressed(cub3d, 's'))
		mult += -1;
	dx = cub3d->player.cos_r * mult * (cub3d->settings.player_speed / 10.0);
	dy = cub3d->player.sin_r * mult * (cub3d->settings.player_speed / 10.0);
	if (can_move(cub3d, cub3d->player.location.x + dx, cub3d->player.location.y,
			PLAYER_COLLISION_RADIUS))
		cub3d->player.location.x += dx;
	if (can_move(cub3d, cub3d->player.location.x, cub3d->player.location.y + dy,
			PLAYER_COLLISION_RADIUS))
		cub3d->player.location.y += dy;
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
	cub3d->player.minimap_pos.x = cub3d->player.location.x * MINIMAP_TILE_SIZE;
	cub3d->player.minimap_pos.y = cub3d->player.location.y * MINIMAP_TILE_SIZE;
	cub3d->player.plane = (t_dvec2){cub3d->plane_len * -cub3d->player.sin_r,
		cub3d->plane_len * cub3d->player.cos_r};
	cub3d->player.direction = (t_dvec2){cub3d->player.cos_r,
		cub3d->player.sin_r};
}
