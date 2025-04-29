/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_loader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:24:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/29 12:41:50 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	load_texture(void *mlx, const char *path, int id)
{
	t_img	*img;
	int		h;
	int		w;

	img = mlx_xpm_file_to_image(mlx, (char *)path, &w, &h);
	if (!img)
		return (true);
	add_asset(id, img);
	return (false);
}

bool	load_assets(void *mlx)
{
	bool error;

	error = false;
	error |= load_texture(mlx, "assets/minimap/minimap_border.xpm", TEXTURE_MINIMAP_BORDER);
	error |= load_texture(mlx, "assets/minimap/minimap_north_indication.xpm", TEXTURE_MINIMAP_NORTH_INDICATION);
	error |= load_texture(mlx, "assets/minimap/minimap_player.xpm", TEXTURE_MINIMAP_PLAYER);
	return (error);
}

void	unload_assets(void *mlx)
{
	int					i;
	t_textures_atlas	*textures_atlas;
	t_texture			*texture;

	i = 0;
	textures_atlas = get_textures_atlas();
	while (i < MAX_TEXTURES)
	{
		texture = textures_atlas->atlas[i++];
		if (texture)
			mlx_destroy_image(mlx, texture);
	}
}
