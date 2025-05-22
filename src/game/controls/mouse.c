/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:54:05 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/22 15:18:16 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void controls_setup_mouse(t_cub3d *cub3d)
{
	mlx_mouse_hide(cub3d->mlx, cub3d->win);
	_info("Mouse Hide Called!");
}

void controls_pause_mouse(t_cub3d *cub3d)
{
	mlx_mouse_show(cub3d->mlx, cub3d->win);
	_info("Mouse Show Called!");
}

void controls_center_mouse(t_cub3d *cub3d)
{
	mlx_mouse_move(cub3d->mlx, cub3d->win, SCREEN_W / 2, SCREEN_H / 2);
}
