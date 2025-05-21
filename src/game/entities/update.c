/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:08:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/21 12:13:43 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_entities(t_cub3d *cub3d)
{
	size_t	i;

	i = 0;
	while (cub3d->entities[i] && i < MAX_ENTITIES)
	{
		cub3d->entities[i].distance_from_player = distance_between(cub3d->entities[i].location,
				cub3d->player.location);
		i++;
	}
}
