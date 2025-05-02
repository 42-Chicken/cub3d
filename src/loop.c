/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:37:33 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/02 09:52:54 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fonts.h"

void	end_loop(t_cub3d *cub3d)
{
	_info("closed !");
	mlx_loop_end(cub3d->mlx);
}

void	unpause_game(t_cub3d *cub3d)
{
	cub3d->menu = CUB3D_MENU_NONE;
	_info("Game unpaused");
}

void	pause_game(t_cub3d *cub3d)
{
	if (cub3d->menu == CUB3D_MENU_PAUSE)
		return ;
	cub3d->menu = CUB3D_MENU_PAUSE;
	igmlx_apply_color_filter(cub3d->rendering_buffer, 0x000000);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer, 0,
		0);
	_info("Game paused");
}

void	loop(t_cub3d *cub3d)
{
	usleep(10000);
	if (cub3d->menu == CUB3D_MENU_PAUSE)
	{
		render_text(cub3d, GTA_FONT_RED_NAME, "G A M E  P A U S E D",
			(t_uvec2){SCREEN_W / 2 - 18 * 10, SCREEN_H / 4});
		mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer,
			0, 0);
	}
	else
	{
		mlx_destroy_image(cub3d->mlx, cub3d->rendering_buffer);
		cub3d->rendering_buffer = mlx_new_image(cub3d->mlx, SCREEN_W, SCREEN_H);
		if (!cub3d->rendering_buffer)
			return (end_loop(cub3d),
				_error("failed to create rendering buffer!"));
		handle_player_movement(cub3d);
		draw_rect(cub3d->rendering_buffer, 0xFFFFFF, (t_uvec2){0, 0},
			(t_uvec2){SCREEN_W, SCREEN_H});
		render_minimap(cub3d);
		render_stats(cub3d);
		mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer,
			0, 0);
	}
}
