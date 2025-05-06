/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:14:38 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/05 09:55:28 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
