/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:25:54 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 10:40:46 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	on_key_pressed(int key, t_cub3d *cub3d)
{
	if (key == XK_Escape)
	{
		if (cub3d->menu != CUB3D_MENU_NONE)
			unpause_game(cub3d);
		else if (cub3d->menu == CUB3D_MENU_NONE)
			pause_game(cub3d);
	}
	if (key == XK_Up)
		cub3d->player.money += 5;
	keycode_controls_items(key, cub3d);
	if (key == XK_e)
		handle_door_interaction(cub3d);
	if (cub3d->key_pressed_index < KEY_PRESSED_MAX && !is_pressed(cub3d, key))
		cub3d->key_pressed[cub3d->key_pressed_index++] = key;
}

void	on_key_released(int key, t_cub3d *cub3d)
{
	size_t	i;
	size_t	y;

	i = KEY_PRESSED_MAX - 1;
	if (cub3d->key_pressed_index > 0 && is_pressed(cub3d, key))
	{
		cub3d->key_pressed_index--;
		while (i >= 0)
		{
			if (cub3d->key_pressed[i] == key)
			{
				y = i;
				cub3d->key_pressed[y] = 0;
				while (y + 1 < KEY_PRESSED_MAX)
				{
					cub3d->key_pressed[y] = cub3d->key_pressed[y + 1];
					y++;
				}
				break ;
			}
			i--;
		}
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
	int	diff;

	cub3d->mouse_position = (t_uvec2){x, y};
	if (cub3d->menu == CUB3D_MENU_PAUSE)
		render_pause_menu(cub3d);
	if (cub3d->menu == CUB3D_MENU_SETTINGS)
		render_options_menu(cub3d);
	if (cub3d->menu == CUB3D_MENU_NONE)
	{
		diff = x - SCREEN_W / 2;
		if (abs(diff) < 5)
			return ;
		if (diff < 0)
			diff = ft_clamp(diff, -1, -1.5);
		else if (diff > 0)
			diff = ft_clamp(diff, 1, 1.5);
		cub3d->player.rotation_angle
			+= ((double)cub3d->settings.player_rotation_speed / 100) * diff;
		controls_center_mouse(cub3d);
	}
}
