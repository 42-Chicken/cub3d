/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:25:54 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/02 12:03:17 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	on_key_pressed(int key, t_cub3d *cub3d)
{
	if (key == XK_p)
	{
		if (cub3d->menu == CUB3D_MENU_PAUSE)
			unpause_game(cub3d);
		else if (cub3d->menu == CUB3D_MENU_NONE)
			pause_game(cub3d);
	}
	if (key == XK_Escape)
		mlx_loop_end(cub3d->mlx);
	if (key == XK_Up)
		cub3d->player.money += 5;
	keycode_controls_items(key, cub3d);
	if (key == XK_l)
	{
	}
	if (key == 'w')
	{
		cub3d->player.direction.x = cub3d->player.cos_r * 0.7f;
		cub3d->player.direction.y = cub3d->player.sin_r * 0.7f;
	}
	if (key == 's')
	{
		cub3d->player.direction.x = -cub3d->player.cos_r * 0.7f;
		cub3d->player.direction.y = -cub3d->player.sin_r * 0.7f;
	}
	if (key == 'a')
	{
		cub3d->player.rotation_angle_add = +0.04f;
	}
	if (key == 'd')
	{
		cub3d->player.rotation_angle_add = -0.04f;
	}
}

void	on_key_released(int key, t_cub3d *cub3d)
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

void	on_mouse_button_down(int key, int x, int y, t_cub3d *cub3d)
{
	(void)x;
	(void)y;
	if (key == 1)
		handle_button_clicks(cub3d);
}

void	on_mouse_move(int x, int y, t_cub3d *cub3d)
{
	cub3d->old_mouse_position = cub3d->mouse_position;
	cub3d->mouse_position = (t_uvec2){x, y};
	if (cub3d->menu == CUB3D_MENU_PAUSE)
		render_pause_menu(cub3d);
}
