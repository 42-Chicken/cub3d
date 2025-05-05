/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:01:07 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/05 08:37:45 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	switch_to_options_menu(t_cub3d *cub3d)
{
	render_game(cub3d);
	igmlx_apply_color_filter(cub3d->rendering_buffer, 0x000000);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer, 0,
		0);
	render_options_menu(cub3d);
	cub3d->menu = CUB3D_MENU_SETTINGS;
}

void	render_pause_menu(t_cub3d *cub3d)
{
	igmlx_simple_copy_to_dest_ignore_null(get_texture(cub3d,
			TEXTURE_PAUSE_MENU_TITLE), cub3d->rendering_buffer,
		(t_uvec2){SCREEN_W / 2 - 445, SCREEN_H / 4 - 25});
	draw_button(cub3d, cub3d->menus_buttons[CUB3D_MENU_PAUSE][0],
		TEXTURE_PAUSE_MENU_RESUME_H);
	draw_button(cub3d, cub3d->menus_buttons[CUB3D_MENU_PAUSE][1],
		TEXTURE_PAUSE_MENU_OPTIONS_H);
	draw_button(cub3d, cub3d->menus_buttons[CUB3D_MENU_PAUSE][2],
		TEXTURE_PAUSE_MENU_QUIT_H);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer, 0,
		0);
}
