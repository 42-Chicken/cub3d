/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_entities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:04:49 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 08:40:15 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_entity(t_cub3d *cub3d, char c, t_uvec2 pos)
{
	t_entity	entity;

	cub3d->map.buffer[pos.y][pos.x] = CUB3D_MAP_FLOOR;
	if (c == 'V')
		entity = new_soldier(pos);
	if (c == 'M')
		entity = new_money(pos);
	if (entity.in_game == true)
		cub3d->entities[cub3d->entity_count++] = entity;
}

void	parse_map_entities(t_cub3d *cub3d)
{
	size_t	i;
	size_t	x;
	size_t	y;

	i = 0;
	while (MAP_SUPPORTED_ENTITIES_CHARS[i])
	{
		y = 0;
		while (y < cub3d->map.height)
		{
			x = 0;
			while (x < ft_strlen(cub3d->map.buffer[y]))
			{
				if (ft_strchr(MAP_SUPPORTED_ENTITIES_CHARS,
						cub3d->map.buffer[y][x]))
					setup_entity(cub3d, cub3d->map.buffer[y][x], (t_uvec2){x,
						y});
				x++;
			}
			y++;
		}
		i++;
	}
}
