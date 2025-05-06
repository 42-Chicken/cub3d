/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:50:26 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 09:48:43 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_button_clicks(t_cub3d *cub3d)
{
	t_button	button;
	int			i;

	i = 0;
	if (cub3d->menu == CUB3D_MENU_NONE)
		return ;
	while (i < MENU_MAX_BTNS)
	{
		button = cub3d->menus_buttons[cub3d->menu][i];
		if (button.texture && fast_is_between((t_vec2){cub3d->mouse_position.x,
				cub3d->mouse_position.y}, (t_vec2){button.pos.x - 5,
			button.pos.y - 5}, (t_vec2){button.pos.x + button.texture->width
			+ 5, button.pos.y + button.texture->height + 5}))
		{
			if (button.type == CUB3D_BUTTON_DEFAULT)
				button.button_callback(button.button_args);
			else
				button.incrementor_callback(button.incrementor_args);
			break ;
		}
		i++;
	}
}

void	draw_button(t_cub3d *cub3d, t_button button,
		t_textures_definition texture_hover)
{
	t_texture	*img;

	img = button.texture;
	if (fast_is_between((t_vec2){cub3d->mouse_position.x,
			cub3d->mouse_position.y}, (t_vec2){button.pos.x - 5, button.pos.y
		- 5}, (t_vec2){button.pos.x + img->width + 5, button.pos.y
		+ img->height + 5}))
		img = get_texture(cub3d, texture_hover);
	igmlx_simple_copy_to_dest(img, cub3d->rendering_buffer, button.pos);
}
