/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:53:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/22 08:54:45 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_entities(t_cub3d *cub3d)
{
	cub3d->entities[0].health = 10;
	cub3d->entities[0].location = cub3d->player.location;
	cub3d->entities[0].textures[0] = TEXTURE_ENTITY_GUARD;
	cub3d->entities[0].type = CUB3D_ENTITY_OFFICER;
	cub3d->entities[0].in_game = true;
}
