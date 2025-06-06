/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:13:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/06 09:24:18 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_textures(t_entity *money)
{
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_RIGHT] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_RIGHT] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_RIGHT] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_BACK_LEFT] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_LEFT] = TEXTURE_ENTITY_BULLET;
	money->textures[CUB3D_ENTITY_TEXTURE_FRONT_LEFT] = TEXTURE_ENTITY_BULLET;
}

static bool handle_player_damage(t_cub3d *cub3d, t_entity *entity)
{
	if (entity->distance_from_player < 1.25 && entity->flag == 1)
	{
		entity->in_game = false;
		cub3d->player.health -= 10;
		cub3d->damage_screen.is_anim = true;
		cub3d->damage_screen.time_start = gettime();
		return (true);
	}
	return (false);
}

static bool	handle_damage(t_cub3d *cub3d, t_entity *entity)
{
	size_t	i;

	i = 0;
	while (i < cub3d->entity_count && entity->flag == 0)
	{
		if (cub3d->entities[i].in_game && &cub3d->entities[i] != entity)
		{
			if ((cub3d->entities[i].type == CUB3D_ENTITY_OFFICER
					|| cub3d->entities[i].type == CUB3D_ENTITY_RAT)
				&& distance_between((t_dvec2){entity->location.x + 0.5,
					entity->location.y + 0.5},
					cub3d->entities[i].location) < 1.25)
			{
				entity->in_game = false;
				cub3d->entities[i].health -= 10;
				if (cub3d->entities[i].health <= 0)
					cub3d->entities[i].in_game = false;
				return (true);
			}
		}
		i++;
	}
	return (handle_player_damage(cub3d, entity));
}

void	update_bullet(t_cub3d *cub3d, t_entity *entity)
{
	if (map_is_wall(cub3d, entity->location.x, entity->location.y)
		|| entity->distance_from_player > 60)
	{
		entity->in_game = false;
		return ;
	}
	if (handle_damage(cub3d, entity))
		return ;
	entity->location.x += cos(entity->rotation_angle) * 0.5;
	entity->location.y += sin(entity->rotation_angle) * 0.5;
}

t_entity	new_bullet(t_dvec2 pos)
{
	t_entity	bullet;

	bullet.in_game = true;
	bullet.not_displayed = false;
	bullet.location = (t_dvec2){pos.x, pos.y};
	setup_textures(&bullet);
	bullet.type = CUB3D_ENTITY_BULLET;
	bullet.minimap_texture = __TEXTURE_NONE__;
	bullet.distance_from_floor = -5;
	bullet.scale = (t_dvec2){0.07, 0.07};
	return (bullet);
}
