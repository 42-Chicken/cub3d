/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:18:49 by efranco           #+#    #+#             */
/*   Updated: 2025/06/06 16:38:46 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	swap_entities(t_cub3d *cub3d, size_t i, size_t j)
{
	t_entity	tmp;

	if (i > MAX_ENTITIES - 1 || j > MAX_ENTITIES - 1)
		return ;
	tmp = cub3d->entities[i];
	cub3d->entities[i] = cub3d->entities[j];
	cub3d->entities[j] = tmp;
}

void	sort_entities(t_cub3d *cub3d)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < cub3d->entity_count)
	{
		j = 0;
		while (j < cub3d->entity_count)
		{
			if (cub3d->entities[i].distance_from_player
				> cub3d->entities[j].distance_from_player)
				swap_entities(cub3d, i, j);
			j++;
		}
		i++;
	}
}

bool	is_entity_locked(t_entity *entity)
{
	return (entity->flag_dir.up_flag && entity->flag_dir.down_flag
		&& entity->flag_dir.right_flag && entity->flag_dir.left_flag);
}

int	build_available_directions(t_entity *entity, int *tab)
{
	int	i;

	i = 0;
	if (!entity->flag_dir.up_flag)
		tab[i++] = 1;
	if (!entity->flag_dir.down_flag)
		tab[i++] = 2;
	if (!entity->flag_dir.right_flag)
		tab[i++] = 3;
	if (!entity->flag_dir.left_flag)
		tab[i++] = 4;
	return (i);
}

t_dvec2	get_direction_target(int direction, t_entity *entity)
{
	t_dvec2	target;

	if (direction == 1)
	{
		entity->rotation_angle = M_PI / 2;
		target = (t_dvec2){entity->location.x, entity->location.y - 1};
	}
	else if (direction == 2)
	{
		entity->rotation_angle = M_PI + M_PI / 2;
		target = (t_dvec2){entity->location.x, entity->location.y + 1};
	}
	else if (direction == 3)
	{
		entity->rotation_angle = M_PI;
		target = (t_dvec2){entity->location.x + 1, entity->location.y};
	}
	else
	{
		entity->rotation_angle = 0;
		target = (t_dvec2){entity->location.x - 1, entity->location.y};
	}
	return (target);
}
