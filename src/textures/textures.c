/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:14:38 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/29 12:33:22 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

t_textures_atlas	*get_textures_atlas(void)
{
	static t_textures_atlas	atlas = {};

	return (&atlas);
}

void	add_asset(int id, t_img *img)
{
	t_textures_atlas	*textures_atlas;

	textures_atlas = get_textures_atlas();
	if (id < MAX_TEXTURES)
	{
		textures_atlas->atlas[id] = img;
	}
}

t_texture	*get_texture(int id)
{
	t_textures_atlas	*textures_atlas;

	textures_atlas = get_textures_atlas();
	return (textures_atlas->atlas[id]);
}
