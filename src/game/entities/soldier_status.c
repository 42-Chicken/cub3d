/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soldier_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:22:44 by efranco           #+#    #+#             */
/*   Updated: 2025/06/06 16:36:06 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	soldier_attaque(t_cub3d *cub3d, t_entity *soldier)
{
	t_cub3d_map	map_info;
	t_dvec2		target_angle;

	if (soldier->distance_from_player < 50 && is_walkable(cub3d->map.buffer,
			soldier->location))
	{
		map_info.map = cub3d->map.buffer;
		map_info.width = SCREEN_W / TILESIZE;
		map_info.height = SCREEN_H / TILESIZE;
		map_info.soldier_pos = soldier->location;
		map_info.target_pos = cub3d->player.location;
		target_angle = a_star_cub3d(map_info);
		if (target_angle.x != -1.0 && target_angle.y != -1.0)
			soldier_thing(cub3d, soldier, target_angle);
		else
			soldier->modattack = false;
	}
	else
		soldier->modattack = false;
}

void	spawn_bullet(t_cub3d *cub3d, t_entity *soldier)
{
	if (cub3d->entity_count + 1 < MAX_ENTITIES)
	{
		cub3d->entities[cub3d->entity_count] = new_bullet(soldier->location, 1);
		cub3d->entities[cub3d->entity_count].rotation_angle
			= soldier->rotation_angle + M_PI;
		cub3d->entities[cub3d->entity_count].flag = 1;
		cub3d->entity_count++;
	}
}

void	soldier_shot(t_cub3d *cub3d, t_entity *soldier)
{
	long	time;

	time = gettime();
	if (((soldier->type == CUB3D_ENTITY_OFFICER
				&& soldier->distance_from_player < 5)
			|| (soldier->type == CUB3D_ENTITY_RAT
				&& soldier->distance_from_player < 1.5)) && time
		- soldier->cd > 1000)
	{
		if (soldier->type == CUB3D_ENTITY_OFFICER)
		{
			spawn_bullet(cub3d, soldier);
			soldier->cd = time;
		}
		else if (soldier->type == CUB3D_ENTITY_RAT)
		{
			cub3d->player.health -= 5;
			soldier->cd = time;
			cub3d->damage_screen.is_anim = true;
			cub3d->damage_screen.time_start = gettime();
		}
	}
}

void	update_active_entity(t_cub3d *cub3d, t_entity *entity)
{
	entity->distance_from_player = distance_between(entity->location,
			cub3d->player.location);
	if (entity->type == CUB3D_ENTITY_OFFICER
		|| entity->type == CUB3D_ENTITY_RAT)
	{
		reset_entity_flags(entity);
		soldier_patern(entity, cub3d);
		soldier_attaque(cub3d, entity);
		soldier_shot(cub3d, entity);
	}
	update_interactions(cub3d, entity);
}

void	remove_inactive_entity(t_cub3d *cub3d, size_t i)
{
	size_t	j;
	size_t	d;

	d = 0;
	ft_bzero(&cub3d->entities[i], sizeof(t_entity));
	j = i + 1;
	while (j < cub3d->entity_count)
	{
		swap_entities(cub3d, i + d++, j++);
	}
	cub3d->entity_count--;
}
