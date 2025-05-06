/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   money_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:51:26 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 09:16:43 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_stats_money(t_cub3d *cub3d, t_texture *item)
{
	char	money[8];

	money[0] = '$';
	custom_itoa(cub3d->player.money, (char *)&money + 1);
	render_text(cub3d, GTA_FONT_BLUE_NAME, money, (t_uvec2){SCREEN_W
		- item->width - RIGHT_HUD_OFFSET * 2.2 - ft_strlen(money) * 18,
		item->height - RIGHT_HUD_OFFSET - 50});
}
