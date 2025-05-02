/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:22:39 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/02 09:53:12 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fonts.h"

void	init_mlx_hooks(t_cub3d *cub3d)
{
	mlx_hook(cub3d->win, DestroyNotify, 0, (int (*)(void *)) & end_loop, cub3d);
	mlx_hook(cub3d->win, FocusOut, FocusChangeMask, (int (*)(void *)) & pause_game, cub3d);

	mlx_hook(cub3d->win, 4, 0, (int (*)(void *)) & on_mouse_scrool_down, cub3d);
	mlx_hook(cub3d->win, 5, 0, (int (*)(void *)) & on_mouse_scrool_up, cub3d);

	mlx_hook(cub3d->win, KeyPress, KeyPressMask,
		(int (*)(void *)) & on_key_pressed, cub3d);
	mlx_hook(cub3d->win, KeyRelease, KeyReleaseMask,
		(int (*)(void *)) & on_key_released, cub3d);
	mlx_loop_hook(cub3d->mlx, (int (*)(void *)) & loop, cub3d);
}

bool	init_mlx(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		return (_error("failed to init mlx!"), false);
	if (load_assets(cub3d) == true)
		return (destroy_mlx(cub3d), _error("failed to load textures !"), false);
	igmlx_load_font(cub3d, GTA_FONT, GTA_FONT_BLUE_NAME,
		(t_igmlx_font_params){GTA_FONT_BLUE_COLOR, 1, (t_uvec2){30, 0}});
	igmlx_load_font(cub3d, GTA_FONT, GTA_FONT_RED_NAME,
		(t_igmlx_font_params){GTA_FONT_RED_COLOR, 1, (t_uvec2){30, 0}});
	igmlx_load_font(cub3d, GTA_FONT, GTA_FONT_YELLOW_NAME,
		(t_igmlx_font_params){GTA_FONT_YELLOW_COLOR, 1, (t_uvec2){30, 0}});
	igmlx_load_font(cub3d, GTA_FONT, GTA_FONT_BLACK_NAME,
		(t_igmlx_font_params){GTA_FONT_BLACK_COLOR, 1, (t_uvec2){30, 0}});
	cub3d->win = mlx_new_window(cub3d->mlx, SCREEN_W, SCREEN_H,
			"GTA III (raycasting)");
	if (!cub3d->win)
		return (_error("failed to create new window!"), false);
	cub3d->rendering_buffer = mlx_new_image(cub3d->mlx, SCREEN_W, SCREEN_H);
	if (!cub3d->rendering_buffer)
		return (_error("failed to create rendering buffer!"), false);
	return (true);
}

bool	destroy_mlx(t_cub3d *cub3d)
{
	if (!cub3d->mlx)
		return (false);
	igmlx_destroy_fonts_list(cub3d, &cub3d->fonts);
	unload_assets(cub3d);
	if (cub3d->rendering_buffer)
		mlx_destroy_image(cub3d->mlx, cub3d->rendering_buffer);
	if (cub3d->win)
		mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free(cub3d->mlx);
	return (true);
}
