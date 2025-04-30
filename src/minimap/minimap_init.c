/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:40:39 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/30 14:19:55 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

 void	fill_minimap_texture(t_cub3d *cub3d, t_texture *minimap)
{
	size_t	x;
	size_t	y;
	t_color	color;

	y = 0;
	while (y < cub3d->map.height)
	{
		x = 0;
		while (x < cub3d->map.width)
		{
			if (map_is_floor(cub3d, x, y))
				color = 0xFF0000;
			else if (map_is_void(cub3d, x, y))
				color = 0x0000FF;
			else
				color = 0x00FF00;
			if (x == (size_t)cub3d->player.position.x
				&& y == (size_t)cub3d->player.position.y)
				color = 0xFF00FF;
			draw_rect(minimap, color, (t_uvec2){x * MINIMAP_TILE_SIZE, y
				* MINIMAP_TILE_SIZE}, (t_uvec2){x * MINIMAP_TILE_SIZE
				+ MINIMAP_TILE_SIZE, y * MINIMAP_TILE_SIZE
				+ MINIMAP_TILE_SIZE});
			x++;
		}
		y++;
	}
}

static bool	create_minimap_texture(t_cub3d *cub3d)
{
	t_img	*minimap;
	// int y;
	minimap = mlx_new_image(cub3d->mlx, cub3d->map.width * MINIMAP_TILE_SIZE,
			cub3d->map.height * MINIMAP_TILE_SIZE);
	if (!minimap)
		return (_error("failed to create minimap image !"), true);
	fill_minimap_texture(cub3d, minimap);
	// add_asset(cub3d, TEXTURE_MINIMAP, mlx_xpm_file_to_image(cub3d->mlx, "assets/floor.xpm", (int *)&y, (int *)&y));
	add_asset(cub3d, TEXTURE_MINIMAP, minimap);
	return (false);
}

bool	init_minimap(t_cub3d *cub3d)
{
	t_texture	*border;
	t_texture	*player;

	border = get_texture(cub3d, TEXTURE_MINIMAP_BORDER);
	player = get_texture(cub3d, TEXTURE_MINIMAP_PLAYER);
	cub3d->minimap.border_pos = (t_uvec2){MINIMAP_OFFSET, SCREEN_H
		- border->height - MINIMAP_OFFSET};
	cub3d->minimap.player_pos = (t_uvec2){
		MINIMAP_OFFSET + border->width / 2 -player->width /2 , SCREEN_H
		- border->height / 2 - MINIMAP_OFFSET - player->height / 2
	};
	if (create_minimap_texture(cub3d) == true)
		return (true);
	return (false);
}
