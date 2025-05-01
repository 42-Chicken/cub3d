/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_loader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:24:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 16:55:03 by rguigneb         ###   ########.fr       */
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
