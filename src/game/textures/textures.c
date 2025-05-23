/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:14:38 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 10:59:27 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_asset_link(t_cub3d *cub3d, char link, t_img *img)
{
	if (cub3d->textures_atlas.links_count + 1 < MAX_TEXTURES)
	{
		cub3d->textures_atlas.links[cub3d->textures_atlas.links_count] = \
		(t_texture_link){link, img};
		cub3d->textures_atlas.links_count++;
	}
}

void	add_asset(t_cub3d *cub3d, int id, t_img *img)
{
	if (id < MAX_TEXTURES)
	{
		cub3d->textures_atlas.atlas[id] = img;
		cub3d->textures_loaded++;
	}
}

t_texture	*get_texture(t_cub3d *cub3d, int id)
{
	return (cub3d->textures_atlas.atlas[id]);
}

t_texture	*get_linked_texture(t_cub3d *cub3d, char link)
{
	size_t	i;

	i = 0;
	while (cub3d->textures_atlas.links[i].texture)
	{
		if (cub3d->textures_atlas.links[i].link == link)
			return (cub3d->textures_atlas.links[i].texture);
		i++;
	}
	return (NULL);
}
