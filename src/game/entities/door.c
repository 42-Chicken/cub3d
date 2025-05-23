/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 10:53:16 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_textures(t_entity *money)
{
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT] = TEXTURE_42;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_RIGHT] = TEXTURE_42;
	money->textures[CUB3D_ENTITY_TEXTURE_RIGHT] = TEXTURE_42;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_RIGHT] = TEXTURE_42;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK] = TEXTURE_42;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_LEFT] = TEXTURE_42;
	money->textures[CUB3D_ENTITY_TEXTURE_LEFT] = TEXTURE_42;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_LEFT] = TEXTURE_42;
}

t_entity	*get_door_at_position(t_cub3d *cub3d, double x, double y)
{
	size_t	i;
	double	dx;
	double	dy;
	double	dist;

	i = 0;
	while (i < cub3d->entity_count)
	{
		if (cub3d->entities[i].type == CUB3D_ENTITY_DOOR)
		{
			dx = cub3d->entities[i].location.x - x;
			dy = cub3d->entities[i].location.y - y;
			dist = sqrt(dx * dx + dy * dy);
			if (dist <= 1.5 && distance_between(cub3d->entities[i].location,
					cub3d->player.location) > 0.75)
				return (&cub3d->entities[i]);
		}
		i++;
	}
	return (NULL);
}

void	interact_with_door(t_cub3d *cub3d, t_entity *entity)
{
	if (map_is_outside_map_buffer(cub3d, (int)entity->location.x,
			(int)entity->location.y))
		return ;
	if (map_get_wall(cub3d, (int)entity->location.x,
			(int)entity->location.y) == CUB3D_MAP_DOOR)
		cub3d->map.buffer[(int)entity->location.y][(int)entity->location.x] \
		= CUB3D_MAP_FLOOR;
	else
		cub3d->map.buffer[(int)entity->location.y][(int)entity->location.x] \
		= CUB3D_MAP_DOOR;
}

void	handle_door_interaction(t_cub3d *cub3d)
{
	t_dvec2		front_pos;
	t_entity	*door;

	front_pos.x = cub3d->player.location.x + cub3d->player.direction.x * 1.5;
	front_pos.y = cub3d->player.location.y + cub3d->player.direction.y * 1.5;
	door = get_door_at_position(cub3d, front_pos.x, front_pos.y);
	if (door)
		interact_with_door(cub3d, door);
}

t_entity	new_door(t_uvec2 pos)
{
	t_entity	door;

	door.in_game = true;
	door.not_displayed = true;
	door.location = (t_dvec2){pos.x + 0.5, pos.y + 0.5};
	setup_textures(&door);
	door.type = CUB3D_ENTITY_DOOR;
	door.minimap_texture = TEXTURE_MINIMAP_DOOR;
	door.rotation_angle = M_PI / 2;
	door.scale = (t_dvec2){1, 1};
	return (door);
}
