/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:08:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/03 15:49:32 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define EPSILON 0.001

static void	swap_entities(t_cub3d *cub3d, size_t i, size_t j)
{
	t_entity	tmp;

	if (i > MAX_ENTITIES - 1 || j > MAX_ENTITIES - 1)
		return ;
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
			entity->rotation_angle = M_PI / 2;
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
			entity->rotation_angle = M_PI + M_PI / 2;
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
			entity->rotation_angle = M_PI;
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
			entity->rotation_angle = 0;
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
void	soldier_attaque(t_cub3d *cub3d, t_entity *soldier)
{
	t_cub3d_map	map_info;
	t_dvec2		target_angle;

	if (soldier->distance_from_player < 30 && is_walkable(cub3d->map.buffer,
			(t_dvec2){soldier->location.x, soldier->location.y}))
	{
		map_info.map = cub3d->map.buffer;
		map_info.width = SCREEN_W / TILESIZE;
		map_info.height = SCREEN_H / TILESIZE;
		map_info.soldier_pos.x = soldier->location.x;
		map_info.soldier_pos.y = soldier->location.y;
		map_info.target_pos.x = cub3d->player.location.x;
		map_info.target_pos.y = cub3d->player.location.y;
		target_angle = a_star_cub3d(map_info);
		if (target_angle.x != -1.0 && target_angle.y != -1.0)
		{
			if (soldier->distance_from_player > 1.5
				&& is_walkable(cub3d->map.buffer, (t_dvec2){soldier->location.x,
					soldier->location.y}))
			{
				soldier->modattack = true;
				soldier->rotation_angle = entity_look_at_player(cub3d, soldier)
					+ M_PI;
				soldier->location.x += target_angle.x * 0.04;
				soldier->location.y += target_angle.y * 0.04;
			}
		}
		else
		{
			soldier->modattack = false;
		}
	}
	else
	{
		soldier->modattack = false;
	}
}
void	soldier_shot(t_cub3d *cub3d, t_entity *soldier)
{
	long	time;

	time = gettime();
	if (soldier->distance_from_player < 5 && time - soldier->cd > 2000)
	{
		cub3d->player.health -= 5;
		soldier->cd = time;
		cub3d->damage_screen.is_anim = true;
		cub3d->damage_screen.time_start = gettime();
	}
}
void	update_entities(t_cub3d *cub3d)
{
	size_t	i;
	size_t	j;
	size_t	d;

	i = 0;
	while (i < cub3d->entity_count)
	{
		j = i + 1;
		if (cub3d->entities[i].in_game)
		{
			cub3d->entities[i].distance_from_player = distance_between(cub3d->entities[i].location,
					cub3d->player.location);
			if (cub3d->entities[i].type == CUB3D_ENTITY_OFFICER)
			{
				cub3d->entities[i].flag_dir.up_flag = false;
				cub3d->entities[i].flag_dir.down_flag = false;
				cub3d->entities[i].flag_dir.right_flag = false;
				cub3d->entities[i].flag_dir.left_flag = false;
				soldier_patern(&cub3d->entities[i], cub3d);
				soldier_attaque(cub3d, &cub3d->entities[i]);
				soldier_shot(cub3d, &cub3d->entities[i]);
			}
			update_interactions(cub3d, &cub3d->entities[i]);
		}
		else
		{
			d = 0;
			while (j < cub3d->entity_count)
			{
				swap_entities(cub3d, i + d++, j++);
			}
			cub3d->entity_count--;
		}
		i++;
	}
	sort_entities(cub3d);
}
