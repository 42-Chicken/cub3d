/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:22:39 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/28 15:49:42 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_mlx_hooks(t_cub3d *cub3d)
{
	mlx_hook(cub3d->win, DestroyNotify, 0, (int (*)(void *))&end_loop, cub3d);
	mlx_loop_hook(cub3d->mlx, (int (*)(void *))&loop, cub3d);
}

bool init_mlx(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		return (_error("failed to init mlx!"), false);
	cub3d->win = mlx_new_window(cub3d->mlx, SCREEN_W, SCREEN_H, "GTA III (raycasting)");
	if (!cub3d->win)
		return (_error("failed to create new window!"), false);
	cub3d->rendering_buffer = mlx_new_image(cub3d->mlx, SCREEN_W, SCREEN_H);
	if (!cub3d->rendering_buffer)
		return (_error("failed to create rendering buffer!"), false);
	// load_textures
	return (true);
}

bool destroy_mlx(t_cub3d *cub3d)
{
	// load_textures
	mlx_destroy_image(cub3d->mlx, cub3d->rendering_buffer);
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free(cub3d->mlx);
	return (true);
}
