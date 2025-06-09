/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_random.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:19:54 by efranco           #+#    #+#             */
/*   Updated: 2025/06/06 16:35:45 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	block_direction(t_entity *entity, int direction)
{
	if (direction == 1)
		entity->flag_dir.up_flag = true;
	else if (direction == 2)
		entity->flag_dir.down_flag = true;
	else if (direction == 3)
		entity->flag_dir.right_flag = true;
	else if (direction == 4)
		entity->flag_dir.left_flag = true;
}

t_dvec2	try_direction(t_entity *entity, t_cub3d *cub3d, int direction)
{
	t_dvec2	target;

	target = get_direction_target(direction, entity);
	if (!map_is_wall(cub3d, target.x, target.y))
	{
		entity->targeton = true;
		return (target);
	}
	else
	{
		block_direction(entity, direction);
		return (generate_random_patrol_target(entity, cub3d));
	}
}

t_dvec2	generate_random_patrol_target(t_entity *entity, t_cub3d *cub3d)
{
	t_dvec2	new_target;
	int		tab[4];
	int		available_directions;
	int		selected_direction;

	if (is_entity_locked(entity))
	{
		entity->locked = true;
		return ((t_dvec2){entity->location.x, entity->location.y});
	}
	available_directions = build_available_directions(entity, tab);
	selected_direction = tab[rand() % available_directions];
	new_target = try_direction(entity, cub3d, selected_direction);
	return (new_target);
}

void	reset_entity_flags(t_entity *entity)
{
	entity->flag_dir.up_flag = false;
	entity->flag_dir.down_flag = false;
	entity->flag_dir.right_flag = false;
	entity->flag_dir.left_flag = false;
}

void	set_movement_flags(t_entity *soldier)
{
	if (soldier->location.x < soldier->target.x)
		soldier->flag_dir.right_flag = true;
	else if (soldier->location.x > soldier->target.x)
		soldier->flag_dir.left_flag = true;
	else if (soldier->location.y < soldier->target.y)
		soldier->flag_dir.down_flag = true;
	else if (soldier->location.y > soldier->target.y)
		soldier->flag_dir.up_flag = true;
}
