/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_loader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:24:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/05 08:57:36 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	load_texture(t_cub3d *cub3d, const char *path, int id)
{
	t_img	*img;
	int		h;
	int		w;

	img = mlx_xpm_file_to_image(cub3d->mlx, (char *)path, &w, &h);
	if (!img)
		return (true);
	add_asset(cub3d, id, img);
	return (false);
}

bool	load_assets(t_cub3d *cub3d)
{
	bool	error;

	error = false;
	error |= load_texture(cub3d, "assets/minimap/minimap_border.xpm",
			TEXTURE_MINIMAP_BORDER);
	error |= load_texture(cub3d, "assets/menus/pause/resume.xpm",
			TEXTURE_PAUSE_MENU_RESUME);
	error |= load_texture(cub3d, "assets/menus/pause/resume_hover.xpm",
			TEXTURE_PAUSE_MENU_RESUME_H);
	error |= load_texture(cub3d, "assets/menus/pause/options.xpm",
			TEXTURE_PAUSE_MENU_OPTIONS);
	error |= load_texture(cub3d, "assets/menus/pause/options_hover.xpm",
			TEXTURE_PAUSE_MENU_OPTIONS_H);
	error |= load_texture(cub3d, "assets/menus/pause/quit.xpm",
			TEXTURE_PAUSE_MENU_QUIT);
	error |= load_texture(cub3d, "assets/menus/pause/quit_hover.xpm",
			TEXTURE_PAUSE_MENU_QUIT_H);
	error |= load_texture(cub3d, "assets/menus/options/plus.xpm",
			TEXTURE_OPTIONS_MENU_PLUS);
	error |= load_texture(cub3d, "assets/menus/options/plus_hover.xpm",
			TEXTURE_OPTIONS_MENU_PLUS_H);
	error |= load_texture(cub3d, "assets/menus/options/minus.xpm",
			TEXTURE_OPTIONS_MENU_MINUS);
	error |= load_texture(cub3d, "assets/menus/options/minus_hover.xpm",
			TEXTURE_OPTIONS_MENU_MINUS_H);
	error |= load_texture(cub3d, "assets/menus/pause/title.xpm",
		TEXTURE_PAUSE_MENU_TITLE);
	error |= load_texture(cub3d, "assets/minimap/minimap_house.xpm",
			TEXTURE_MINIMAP_HOUSE);
	error |= load_texture(cub3d,
			"assets/minimap/minimap_north_indication.xpm",
			TEXTURE_MINIMAP_NORTH_INDICATION);
	error |= load_texture(cub3d, "assets/minimap/minimap_player.xpm",
			TEXTURE_MINIMAP_PLAYER);
	error |= load_texture(cub3d, "assets/pistol.xpm",
			TEXTURE_HUD_PISTOL);
	error |= load_texture(cub3d, "assets/fist.xpm",
			TEXTURE_HUD_HAND);
	error |= load_texture(cub3d, "assets/shotgun.xpm",
			TEXTURE_HUD_SHOTGUN);
	error |= init_minimap(cub3d);
	return (error);
}

void	unload_assets(t_cub3d *cub3d)
{
	int			i;
	t_texture	*texture;

	i = 0;
	while (i < MAX_TEXTURES)
	{
		texture = cub3d->textures_atlas.atlas[i++];
		if (texture)
			mlx_destroy_image(cub3d->mlx, texture);
	}
}
