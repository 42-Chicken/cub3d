/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_loader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:24:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 10:31:29 by rguigneb         ###   ########.fr       */
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
// pthread_mutex_unlock(&cub3d->mutex);
// pthread_mutex_lock(&cub3d->mutex);

bool	load_assets(t_cub3d *cub3d)
{
	bool				error;
	char				**textures_paths;
	size_t				i;

	i = -1;
	create_safe_memory_context();
	textures_paths = ft_split(TEXTURES_PATHS, '\n');
	if (!textures_paths)
		return (true);
	error = false;
	while (textures_paths[++i])
		error |= load_texture(cub3d, textures_paths[i], i);
	error |= init_minimap(cub3d);
	// igmlx_apply_color_filter(get_texture(cub3d, TEXTURE_FLOOR), cub3d->floor_color);
	// igmlx_apply_color_filter(get_texture(cub3d, TEXTURE_SKY), cub3d->ceiling_color);
	exit_safe_memory_context();
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
