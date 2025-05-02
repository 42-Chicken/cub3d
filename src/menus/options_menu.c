/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:01:07 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/02 14:14:39 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	increment_value(t_incrementor_data data)
{
	*data.n += data.i;
}

void	draw_incrementor(t_cub3d *cub3d, char *name, int *n, double incr, int i)
{
	t_uvec2		pos;

	render_text(cub3d, GTA_FONT_YELLOW_NAME, name, (t_uvec2){SCREEN_W / 2 - 445,
		SCREEN_H / 4 - 25});
	pos = (t_uvec2){SCREEN_W / 2 + 325, SCREEN_H / 4 + 160};
	cub3d->menus_buttons[CUB3D_MENU_SETTINGS][i].incrementor_callback = increment_value;
	cub3d->menus_buttons[CUB3D_MENU_SETTINGS][i].incrementor_args = (t_incrementor_data){n,
		incr};
	cub3d->menus_buttons[CUB3D_MENU_SETTINGS][i].pos = pos;
	cub3d->menus_buttons[CUB3D_MENU_SETTINGS][i].texture = get_texture(cub3d,
			TEXTURE_PAUSE_MENU_QUIT);
	draw_button(cub3d, cub3d->menus_buttons[CUB3D_MENU_SETTINGS][i],
		TEXTURE_PAUSE_MENU_QUIT_H);
}

void	render_options_menu(t_cub3d *cub3d)
{
	draw_incrementor(cub3d, "F O V :", (int *)&cub3d->settings.fov, 0.5, 0);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer, 0,
		0);
}
