/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:01:07 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/05 13:02:34 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	decrement_value(t_incrementor_data data)
{
	*data.n -= data.i;
	render_options_menu(data.cub3d);
}
static void	increment_value(t_incrementor_data data)
{
	*data.n += data.i;
	render_options_menu(data.cub3d);
}

void	draw_incrementor(t_cub3d *cub3d, char *name, int *n, double incr, int i)
{
	t_uvec2		pos;
	char		buffer[255];
	t_button	*btns;

	btns = cub3d->menus_buttons[CUB3D_MENU_SETTINGS];
	custom_itoa(*n, buffer);
	draw_rect(cub3d->rendering_buffer, 0xFFFFFF, (t_uvec2){SCREEN_W / 2 + 225
		- 145, SCREEN_H / 4 + 50 * i - 25}, (t_uvec2){SCREEN_W / 2 + 225 + 70,
		SCREEN_H / 4 + 50 * i + 40});
	render_text(cub3d, GTA_FONT_YELLOW_NAME, name, (t_uvec2){SCREEN_W / 2
		- ft_strlen(name) * 18 - 50, SCREEN_H / 4 + 50 * i - 27});
	pos = (t_uvec2){SCREEN_W / 2 + 225, SCREEN_H / 4 + 50 * i - 25};
	btns[i].incrementor_callback = increment_value;
	btns[i].incrementor_args = (t_incrementor_data){n, incr, cub3d};
	btns[i].pos = pos;
	btns[i].texture = get_texture(cub3d, TEXTURE_OPTIONS_MENU_PLUS);
	draw_button(cub3d, btns[i], TEXTURE_OPTIONS_MENU_PLUS_H);
	render_text(cub3d, GTA_FONT_YELLOW_NAME, buffer, (t_uvec2){SCREEN_W / 2
		+ 225 - 75, SCREEN_H / 4 + 50 * i - 27});
	pos = (t_uvec2){SCREEN_W / 2 + 225 - 140, SCREEN_H / 4 + 50 * i - 25};
	btns[i + 1].incrementor_callback = decrement_value;
	btns[i + 1].incrementor_args = (t_incrementor_data){n, incr, cub3d};
	btns[i + 1].pos = pos;
	btns[i + 1].texture = get_texture(cub3d, TEXTURE_OPTIONS_MENU_MINUS);
	draw_button(cub3d, btns[i + 1], TEXTURE_OPTIONS_MENU_MINUS_H);
}

void	render_options_menu(t_cub3d *cub3d)
{
	draw_incrementor(cub3d, "M O U S E :", (int *)&cub3d->settings.mouse_sens, 1, 0);
	draw_incrementor(cub3d, "F O V :", (int *)&cub3d->settings.fov, 1, 3);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer, 0,
		0);
}
