/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:37:33 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 10:07:12 by rguigneb         ###   ########.fr       */
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
	if (cub3d->menu != CUB3D_MENU_NONE)
		return ;
	cub3d->menu = CUB3D_MENU_PAUSE;
	usleep(100);
	igmlx_apply_color_filter(cub3d->rendering_buffer, 0x000000);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer, 0,
		0);
	render_pause_menu(cub3d);
	_info("Game paused");
}

void	loop(t_cub3d *cub3d)
{
	usleep(10000);
	if (cub3d->menu == CUB3D_MENU_NONE)
		render_game(cub3d);
	cub3d->last_frame_menu = cub3d->menu;
}
