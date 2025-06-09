/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_part_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:21:39 by efranco           #+#    #+#             */
/*   Updated: 2025/06/06 16:28:23 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_movement(t_entity *soldier)
{
	if (soldier->flag_dir.right_flag)
		soldier->location.x += 0.01;
	else if (soldier->flag_dir.left_flag)
		soldier->location.x -= 0.01;
	else if (soldier->flag_dir.down_flag)
		soldier->location.y += 0.01;
	else if (soldier->flag_dir.up_flag)
		soldier->location.y -= 0.01;
}

void	soldier_patern(t_entity *soldier, t_cub3d *cub3d)
{
	if (soldier->modattack == true)
	{
		soldier->targeton = false;
		return ;
	}
	if (soldier->locked == false)
	{
		if (fabs(soldier->location.x - soldier->target.x) < EPSILON
			&& fabs(soldier->location.y - soldier->target.y) < EPSILON)
		{
			soldier->targeton = false;
		}
		if (soldier->targeton == false)
		{
			soldier->target = generate_random_patrol_target(soldier, cub3d);
		}
		reset_entity_flags(soldier);
		set_movement_flags(soldier);
		apply_movement(soldier);
	}
}

void	update_interactions(t_cub3d *cub3d, t_entity *entity)
{
	if (entity->type == CUB3D_ENTITY_MONEY)
		update_money(cub3d, entity);
	if (entity->type == CUB3D_ENTITY_BULLET)
		update_bullet(cub3d, entity);
}

double	entity_look_at_player(t_cub3d *cub3d, t_entity *soldier)
{
	double	dx;
	double	dy;
	double	angle_to_player;

	dx = cub3d->player.location.x - soldier->location.x;
	dy = cub3d->player.location.y - soldier->location.y;
	angle_to_player = atan2(dy, dx);
	if (angle_to_player < 0)
		angle_to_player += 2.0 * M_PI;
	return (angle_to_player);
}

void	soldier_thing(t_cub3d *cub3d, t_entity *soldier, t_dvec2 target_angle)
{
	if (soldier->distance_from_player > 1.5 && is_walkable(cub3d->map.buffer,
			(t_dvec2){soldier->location.x, soldier->location.y}))
	{
		soldier->modattack = true;
		soldier->rotation_angle = entity_look_at_player(cub3d, soldier) + M_PI;
		soldier->location.x += target_angle.x * 0.04;
		soldier->location.y += target_angle.y * 0.04;
	}
}
