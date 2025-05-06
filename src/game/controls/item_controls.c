/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:14:11 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 09:25:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keycode_controls_items(int key, t_cub3d *cub3d)
{
	if (key == '1')
		cub3d->player.item = TEXTURE_HUD_HAND;
	if (key == '2')
		cub3d->player.item = TEXTURE_HUD_PISTOL;
	if (key == '3')
		cub3d->player.item = TEXTURE_HUD_SHOTGUN;
}
