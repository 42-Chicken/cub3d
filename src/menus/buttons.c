/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:50:26 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/02 12:03:54 by rguigneb         ###   ########.fr       */
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
	while (i < MENU_MAX_BUTTONS)
	{
		button = cub3d->menus_buttons[cub3d->menu][i];
		if (button.callback && button.texture
			&& fast_is_between((t_vec2){cub3d->mouse_position.x,
				cub3d->mouse_position.y}, (t_vec2){button.pos.x - 5,
				button.pos.y - 5}, (t_vec2){button.pos.x + button.texture->width
				+ 5, button.pos.y + button.texture->height + 5}))
		{
			button.callback(cub3d);
			break ;
		}
		i++;
	}
}
