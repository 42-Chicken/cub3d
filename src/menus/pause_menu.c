/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:01:07 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/02 12:09:21 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_button(t_cub3d *cub3d, t_button button, t_textures_definition texture_hover)
{
	t_texture *img;

	img = button.texture;
	if (fast_is_between((t_vec2){cub3d->mouse_position.x, cub3d->mouse_position.y}, (t_vec2){button.pos.x - 5, button.pos.y - 5}, (t_vec2){button.pos.x + img->width + 5,
		button.pos.y + img->height + 5}))
		img = get_texture(cub3d, texture_hover);
	igmlx_simple_copy_to_dest_ignore_null(img, cub3d->rendering_buffer, button.pos);
}

void	render_pause_menu(t_cub3d *cub3d)
{
	t_uvec2 pos;

	igmlx_simple_copy_to_dest_ignore_null(get_texture(cub3d, TEXTURE_PAUSE_MENU_TITLE), cub3d->rendering_buffer,  (t_uvec2){SCREEN_W / 2 - 445, SCREEN_H / 4 - 25});
	pos = (t_uvec2){SCREEN_W / 2 - 425, SCREEN_H / 4 + 160};
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][0].callback = unpause_game;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][0].pos = pos;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][0].texture = get_texture(cub3d, TEXTURE_PAUSE_MENU_RESUME);
	draw_button(cub3d, cub3d->menus_buttons[CUB3D_MENU_PAUSE][0], TEXTURE_PAUSE_MENU_RESUME_H);
	pos = (t_uvec2){SCREEN_W / 2 - 50, SCREEN_H / 4 + 160};
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][1].callback = unpause_game;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][1].pos = (t_uvec2){SCREEN_W / 2 - 50, SCREEN_H / 4 + 160};;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][1].texture = get_texture(cub3d, TEXTURE_PAUSE_MENU_OPTIONS);
	draw_button(cub3d, cub3d->menus_buttons[CUB3D_MENU_PAUSE][1], TEXTURE_PAUSE_MENU_OPTIONS_H);
	pos = (t_uvec2){SCREEN_W / 2 + 325, SCREEN_H / 4 + 160};
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][2].callback = end_loop;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][2].pos = pos;
	cub3d->menus_buttons[CUB3D_MENU_PAUSE][2].texture = get_texture(cub3d, TEXTURE_PAUSE_MENU_QUIT);
	draw_button(cub3d, cub3d->menus_buttons[CUB3D_MENU_PAUSE][2], TEXTURE_PAUSE_MENU_QUIT_H);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer,
		0, 0);
}
