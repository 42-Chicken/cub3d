/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_loader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:24:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 11:13:03 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	load_texture(t_cub3d *cub3d, const char *path, int id)
{
	t_img	*img;
	int		h;
	int		w;

	if (!path)
		return (true);
	if (ft_strchr(path, ' '))
	{
		img = mlx_xpm_file_to_image(cub3d->mlx, (char *)path + 2, &w, &h);
		if (!img)
			return (true);
		add_asset_link(cub3d, path[0], img);
	}
	else
	{
		img = mlx_xpm_file_to_image(cub3d->mlx, (char *)path, &w, &h);
		if (!img)
			return (true);
		add_asset(cub3d, id, img);
	}
	return (false);
}

bool	load_assets(t_cub3d *cub3d)
{
	bool	error;
	char	**textures_paths;
	size_t	i;

	i = -1;
	create_safe_memory_context();
	textures_paths = ft_split(TEXTURES_PATHS, '\n');
	if (!textures_paths)
		return (true);
	error = false;
	error |= load_texture(cub3d, cub3d->north_texture_path, TEXTURE_WALL_NORTH);
	error |= load_texture(cub3d, cub3d->south_texture_path, TEXTURE_WALL_SOUTH);
	error |= load_texture(cub3d, cub3d->east_texture_path, TEXTURE_WALL_EAST);
	error |= load_texture(cub3d, cub3d->west_texture_path, TEXTURE_WALL_WEST);
	while (textures_paths[++i] && error == false)
	{
		error |= load_texture(cub3d, textures_paths[i], i);
		update_loading_screen(cub3d);
	}
	igmlx_apply_color_filter(get_texture(cub3d, TEXTURE_FLOOR), cub3d->floor_color);
	if (!error)
		error |= init_minimap(cub3d);
	exit_safe_memory_context();
	return (error);
}
// usleep(100000);
// igmlx_apply_color_filter(get_texture(cub3d, TEXTURE_FLOOR),
// cub3d->floor_color);
// igmlx_apply_color_filter(get_texture(cub3d, TEXTURE_SKY),
// cub3d->ceiling_color);

void	unload_assets(t_cub3d *cub3d)
{
	size_t		i;
	t_texture	*texture;

	i = 0;
	while (i < MAX_TEXTURES)
	{
		texture = cub3d->textures_atlas.atlas[i++];
		if (texture)
			mlx_destroy_image(cub3d->mlx, texture);
	}
	i = 0;
	while (i < MAX_TEXTURES)
	{
		texture = cub3d->textures_atlas.links[i++].texture;
		if (texture)
			mlx_destroy_image(cub3d->mlx, texture);
	}
}
