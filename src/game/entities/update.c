/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:08:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/27 23:53:43 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define EPSILON 0.001

static void	swap_entities(t_cub3d *cub3d, size_t i, size_t j)
{
	t_entity	tmp;

	tmp = cub3d->entities[i];
	cub3d->entities[i] = cub3d->entities[j];
	cub3d->entities[j] = tmp;
}

static void	sort_entities(t_cub3d *cub3d)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < cub3d->entity_count)
	{
		j = 0;
		while (j < cub3d->entity_count)
		{
			if (cub3d->entities[i].distance_from_player > cub3d->entities[j].distance_from_player)
				swap_entities(cub3d, i, j);
			j++;
		}
		i++;
	}
}
t_dvec2	generate_random_patrol_target(t_entity *entity, t_cub3d *cub3d)
{
	t_dvec2	new_target;
	int		tab[4];
	int		i;
	int		val;

	i = 0;
	if (entity->flag_dir.up_flag && entity->flag_dir.down_flag
		&& entity->flag_dir.right_flag && entity->flag_dir.left_flag)
	{
		entity->locked = true;
		new_target.x = entity->location.x;
		new_target.y = entity->location.y;
		return (new_target);
	}
	if (!entity->flag_dir.up_flag)
		tab[i++] = 1;
	if (!entity->flag_dir.down_flag)
		tab[i++] = 2;
	if (!entity->flag_dir.right_flag)
		tab[i++] = 3;
	if (!entity->flag_dir.left_flag)
		tab[i++] = 4;
	val = tab[rand() % i];
	if (val == 1)
	{
		if (!map_is_wall(cub3d, entity->location.x, entity->location.y - 1))
		{
			new_target.x = entity->location.x;
			new_target.y = entity->location.y - 1;
			entity->targeton = true;
			return (new_target);
		}
		else
		{
			entity->flag_dir.up_flag = true;
			return (generate_random_patrol_target(entity, cub3d));
		}
	}
	else if (val == 2)
	{
		if (!map_is_wall(cub3d, entity->location.x, entity->location.y + 1))
		{
			new_target.x = entity->location.x;
			new_target.y = entity->location.y + 1;
			entity->targeton = true;
			return (new_target);
		}
		else
		{
			entity->flag_dir.down_flag = true;
			return (generate_random_patrol_target(entity, cub3d));
		}
	}
	else if (val == 3)
	{
		if (!map_is_wall(cub3d, entity->location.x + 1, entity->location.y))
		{
			new_target.x = entity->location.x + 1;
			new_target.y = entity->location.y;
			entity->targeton = true;
			return (new_target);
		}
		else
		{
			entity->flag_dir.right_flag = true;
			return (generate_random_patrol_target(entity, cub3d));
		}
	}
	else if (val == 4)
	{
		if (!map_is_wall(cub3d, entity->location.x - 1, entity->location.y))
		{
			new_target.x = entity->location.x - 1;
			new_target.y = entity->location.y;
			entity->targeton = true;
			return (new_target);
		}
		else
		{
			entity->flag_dir.left_flag = true;
			return (generate_random_patrol_target(entity, cub3d));
		}
	}
	new_target.x = entity->location.x;
	new_target.y = entity->location.y;
	return (new_target);
}
void	soldier_patern(t_entity *soldier, t_cub3d *cub3d)
{
	(void)(cub3d);
	if (soldier->locked == false)
	{
		if (fabs(soldier->location.x - soldier->target.x) < EPSILON
			&& fabs(soldier->location.y - soldier->target.y) < EPSILON)
		{
			soldier->targeton = false;
		}
		if (soldier->targeton == false)
			soldier->target = generate_random_patrol_target(soldier, cub3d);
		soldier->flag_dir.up_flag = false;
		soldier->flag_dir.down_flag = false;
		soldier->flag_dir.right_flag = false;
		soldier->flag_dir.left_flag = false;
		if (soldier->location.x < soldier->target.x)
			soldier->location.x += 0.01;
		else if (soldier->location.x > soldier->target.x)
			soldier->location.x -= 0.01;
		else if (soldier->location.y < soldier->target.y)
			soldier->location.y += 0.01;
		else if (soldier->location.y > soldier->target.y)
			soldier->location.y -= 0.01;
	}
	else
	{
		return ;
	}
}
static void	update_interactions(t_cub3d *cub3d, t_entity *entity)
{
	if (entity->type == CUB3D_ENTITY_MONEY)
		update_money(cub3d, entity);
}

void	update_entities(t_cub3d *cub3d)
{
	size_t	i;

	i = 0;
	while (i < cub3d->entity_count)
	{
		if (cub3d->entities[i].in_game)
		{
			cub3d->entities[i].flag_dir.up_flag = false;
			cub3d->entities[i].flag_dir.down_flag = false;
			cub3d->entities[i].flag_dir.right_flag = false;
			cub3d->entities[i].flag_dir.left_flag = false;
			soldier_patern(&cub3d->entities[i], cub3d);
			soldier_attaque();
			cub3d->entities[i].distance_from_player = distance_between(cub3d->entities[i].location,
					cub3d->player.location);
			update_interactions(cub3d, &cub3d->entities[i]);
		}
		i++;
	}
	sort_entities(cub3d);
}
