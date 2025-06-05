/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_entities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:04:49 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/05 12:21:25 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_entity(t_cub3d *cub3d, char c, t_uvec2 pos)
{
	t_entity	entity;

	if (cub3d->entity_count >= MAX_ENTITIES)
		return ;
	cub3d->map.buffer[pos.y][pos.x] = CUB3D_MAP_FLOOR;
	if (c == 'V')
		entity = new_soldier(pos);
	else if (c == 'M')
		entity = new_money(pos);
	else if (c == 'L')
		entity = new_lamp(pos);
	else if (c == 'A')
		entity = new_fire_hydrant(pos);
	else if (c == 'f')
		entity = new_fire_baril(pos);
	else if (c == 'R')
		entity = new_rat(pos);
	else if (c == 'T')
		entity = new_trashcan(pos);
	else if (c == 't')
		entity = new_tree1(pos);
	else if (c == '2')
		entity = new_tree2(pos);
	else if (c == 'D')
	{
		cub3d->map.buffer[pos.y][pos.x] = CUB3D_MAP_DOOR;
		entity = new_door(pos);
	}
	else
		return ;
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
