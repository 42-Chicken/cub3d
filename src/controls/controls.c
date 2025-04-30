/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:25:54 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/30 11:19:38 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void on_key_pressed(int key, t_cub3d *cub3d)
{
	if (key == 'w')
	{
		cub3d->player.direction.x = cos(cub3d->player.rotation_angle) * 3.5f;
		cub3d->player.direction.y = sin(cub3d->player.rotation_angle) * 3.5f;
	}
	if (key == 's')
	{
		cub3d->player.direction.x = -cos(cub3d->player.rotation_angle) * 3.5f;
		cub3d->player.direction.y = -sin(cub3d->player.rotation_angle) * 3.5f;
	}
	if (key == 'a')
	{
		cub3d->player.rotation_angle_add = +0.04f;
	}
	if (key == 'd')
	{
		cub3d->player.rotation_angle_add = -0.04f;
	}

	if (key == 'i')
	{
		cub3d->settings.fFar += .5f;
	}
	if (key == 'k')
	{
		cub3d->settings.fFar -= .5f;
	}

	if (key == 'j')
	{
		cub3d->settings.fNear += .5f;
	}
	if (key == 'l')
	{
		cub3d->settings.fNear -= .5f;
	}
}

void on_key_released(int key, t_cub3d *cub3d)
{
	if (key == 'w')
	{
		cub3d->player.direction.x = 0;
		cub3d->player.direction.y = 0;
	}
	if (key == 's')
	{
		cub3d->player.direction.x = 0;
		cub3d->player.direction.y = 0;
	}
	if (key == 'a')
	{
		cub3d->player.rotation_angle_add = 0;
	}
	if (key == 'd')
	{
		cub3d->player.rotation_angle_add = 0;
	}
}
