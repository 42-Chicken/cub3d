/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:43:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/02 14:24:12 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_types(t_button *buttons, t_e_button_type type)
{
	size_t	i;

	i = 0;
	while (i < MENU_MAX_BUTTONS)
	{
		buttons[i++].type = type;
	}
}

static void	init_pause_menu(t_cub3d *cub3d)
{
	t_uvec2	pos;

	init_types(cub3d->menus_buttons[CUB3D_MENU_PAUSE], CUB3D_BUTTON_DEFAULT);
	pos = (t_uvec2){SCREEN_W / 2 - 425, SCREEN_H / 4 + 160};
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][0].button_callback = unpause_game;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][0].button_args = cub3d;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][0].pos = pos;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][0].texture = get_texture(cub3d,
			TEXTURE_PAUSE_MENU_RESUME);
	pos = (t_uvec2){SCREEN_W / 2 - 50, SCREEN_H / 4 + 160};
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][1].button_callback = switch_to_options_menu;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][1].button_args = cub3d;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][1].pos = (t_uvec2){SCREEN_W / 2 - 50,
		SCREEN_H / 4 + 160};
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][1].texture = get_texture(cub3d,
			TEXTURE_PAUSE_MENU_OPTIONS);
	pos = (t_uvec2){SCREEN_W / 2 + 325, SCREEN_H / 4 + 160};
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][2].button_callback = end_loop;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][2].button_args = cub3d;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][2].pos = pos;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][2].texture = get_texture(cub3d,
			TEXTURE_PAUSE_MENU_QUIT);
}

void	init_menus(t_cub3d *cub3d)
{
	init_pause_menu(cub3d);
	init_types(cub3d->menus_buttons[CUB3D_MENU_SETTINGS],
		CUB3D_BUTTON_INCREMENTOR);
}
