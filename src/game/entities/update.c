/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:08:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 09:02:17 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

void	update_entities(t_cub3d *cub3d)
{
	size_t	i;

	i = 0;
	while (i < cub3d->entity_count)
	{
		if (cub3d->entities[i].in_game)
		{
			cub3d->entities[i].distance_from_player = \
			distance_between(cub3d->entities[i].location,
				cub3d->player.location);
			update_interactions(cub3d, &cub3d->entities[i]);
		}
		i++;
	}
	sort_entities(cub3d);
}
