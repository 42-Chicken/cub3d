/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:37:33 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/22 15:19:08 by rguigneb         ###   ########.fr       */
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
	controls_setup_mouse(cub3d);
	controls_center_mouse(cub3d);
	_info("Game unpaused");
}

void	pause_game(t_cub3d *cub3d)
{
	if (cub3d->menu != CUB3D_MENU_NONE || cub3d->loaded == false
		|| cub3d->tick < 10)
		return ;
	cub3d->menu = CUB3D_MENU_PAUSE;
	controls_pause_mouse(cub3d);
	usleep(10000);
	igmlx_apply_color_filter(cub3d->rendering_buffer, 0x000000);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer, 0,
		0);
	render_pause_menu(cub3d);
	_info("Game paused");
}

void	loop(t_cub3d *cub3d)
{
	if (cub3d->menu == CUB3D_MENU_NONE)
		render_game(cub3d);
	cub3d->last_frame_menu = cub3d->menu;
	cub3d->tick++;
	usleep(100);
}
