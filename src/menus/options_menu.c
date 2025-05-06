/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:01:07 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 13:23:56 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	decrement_value(t_incrementor_data data)
{
	*data.n -= data.i;
	if (*data.n < data.min)
		*data.n = data.min;
	if (*data.n > data.max)
		*data.n = data.max;
	switch_to_options_menu(data.cub3d);
}

static void	increment_value(t_incrementor_data data)
{
	*data.n += data.i;
	if (*data.n < data.min)
		*data.n = data.min;
	if (*data.n > data.max)
		*data.n = data.max;
	switch_to_options_menu(data.cub3d);
}

void	draw_incrementor(t_cub3d *cub3d, char *name, t_incrementor_data data,
		int i)
{
	t_uvec2		pos;
	char		buffer[255];
	t_button	*btns;
	int			distance;

	btns = cub3d->menus_buttons[CUB3D_MENU_SETTINGS];
	custom_itoa(*data.n, buffer);
	render_text(cub3d, GTA_FONT_YELLOW_NAME, name, (t_uvec2){SCREEN_W / 2
		- ft_strlen(name) * 18 - 50, SCREEN_H / 4 + 50 * i - 27});
	pos = (t_uvec2){SCREEN_W / 2 + 225 + 125 - 70, SCREEN_H / 4 + 50 * i - 25};
	btns[i].incrementor_callback = increment_value;
	btns[i].incrementor_args = data;
	btns[i].pos = pos;
	btns[i].texture = get_texture(cub3d, TEXTURE_OPTIONS_MENU_PLUS);
	draw_button(cub3d, btns[i], TEXTURE_OPTIONS_MENU_PLUS_H);
	distance = (225 + 125) - (225 - 140);
	render_text(cub3d, GTA_FONT_RED_NAME, buffer, (t_uvec2){SCREEN_W / 2 - 65
		+ distance - ft_strlen(buffer) * 18 / 2, SCREEN_H / 4 + 50 * i - 27});
	pos = (t_uvec2){SCREEN_W / 2 + 225 - 140, SCREEN_H / 4 + 50 * i - 25};
	btns[i + 1].incrementor_callback = decrement_value;
	btns[i + 1].incrementor_args = data;
	btns[i + 1].pos = pos;
	btns[i + 1].texture = get_texture(cub3d, TEXTURE_OPTIONS_MENU_MINUS);
	draw_button(cub3d, btns[i + 1], TEXTURE_OPTIONS_MENU_MINUS_H);
}

void	render_options_menu(t_cub3d *cub3d)
{
	t_uvec2		pos;
	t_button	*btns;

	btns = cub3d->menus_buttons[CUB3D_MENU_SETTINGS];
	igmlx_simple_copy_to_dest(get_texture(cub3d, TEXTURE_OPTIONS_MENU_TITLE),
		cub3d->rendering_buffer, (t_uvec2){SCREEN_W / 2 - 135, SCREEN_H / 8
		- 50});
	draw_incrementor(cub3d, "M O U S E :",
		(t_incrementor_data){(int *)&cub3d->settings.mouse_sens, 1, 1, 100,
		cub3d}, 0);
	draw_incrementor(cub3d, "F O V :",
		(t_incrementor_data){(int *)&cub3d->settings.fov, 1, 45, 100, cub3d},
		2);
	draw_incrementor(cub3d, "S P E E D",
		(t_incrementor_data){(int *)&cub3d->settings.player_speed, 1, 1, 10,
		cub3d}, 4);
	pos = (t_uvec2){SCREEN_W / 2 - 55, SCREEN_H - SCREEN_H / 4};
	btns[7].type = CUB3D_BUTTON_DEFAULT;
	btns[7].button_callback = switch_to_pause_menu;
	btns[7].button_args = cub3d;
	btns[7].pos = pos;
	btns[7].texture = get_texture(cub3d, TEXTURE_OPTIONS_MENU_BACK);
	draw_button(cub3d, btns[7], TEXTURE_OPTIONS_MENU_BACK_H);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer, 0,
		0);
}

//// draw_incrementor(cub3d, "V O L U M E :",
	// 	(t_incrementor_data){(int *)&cub3d->settings.sounds, 1, 0, 100, cub3d},
	// 	4);
