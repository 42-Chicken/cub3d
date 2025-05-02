/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 08:42:49 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/02 09:13:17 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_stats_health(t_cub3d *cub3d, t_texture *item)
{
	char	health[5];

	health[0] = '\1';
	custom_itoa(cub3d->player.health, (char *)&health + 1);
	render_text(cub3d, GTA_FONT_RED_NAME, health, (t_uvec2){SCREEN_W - item->width - RIGHT_HUD_OFFSET * 2.2
		- ft_strlen(health) * 18, item->height - RIGHT_HUD_OFFSET * 1.7 - 2});
}
