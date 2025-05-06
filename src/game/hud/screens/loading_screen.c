/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:18:07 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 14:45:40 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void update_loading_screen(t_cub3d *cub3d)
{
	t_texture *loading_screen;

	loading_screen = get_texture(cub3d, TEXTURE_LOADING_SCREEN);
	usleep(1000);
	if (!loading_screen)
	{
		draw_rect(cub3d->rendering_buffer, 0x36454f, (t_uvec2){SCREEN_W / 8, SCREEN_H - 30}, (t_uvec2){SCREEN_W - SCREEN_W / 8, SCREEN_H - 20});
		mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer, 0, 0);
	}
	else
	{
		draw_rect(loading_screen, 0x36454f, (t_uvec2){SCREEN_W / 8, SCREEN_H - 30}, (t_uvec2){SCREEN_W - SCREEN_W / 8, SCREEN_H - 20});
		draw_rect(loading_screen, 0x708090, (t_uvec2){SCREEN_W / 8, SCREEN_H - 30}, (t_uvec2){SCREEN_W / 8 + (SCREEN_W / __TEXTURES_COUNT__ / 1.5) * cub3d->textures_loaded, SCREEN_H - 20});
		mlx_put_image_to_window(cub3d->mlx, cub3d->win, loading_screen, 0, 0);
	}
}
