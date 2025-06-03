/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:08:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/03 12:39:50 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			if (cub3d->entities[i].distance_from_player > \
				cub3d->entities[j].distance_from_player)
				swap_entities(cub3d, i, j);
			j++;
		}
		i++;
	}
}

static void	update_interactions(t_cub3d *cub3d, t_entity *entity)
{
	if (entity->type == CUB3D_ENTITY_MONEY)
		update_money(cub3d, entity);
	if (entity->type == CUB3D_ENTITY_BULLET)
		update_bullet(cub3d, entity);
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
			cub3d->entities[i].distance_from_player = \
			distance_between(cub3d->entities[i].location,
					cub3d->player.location);
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
