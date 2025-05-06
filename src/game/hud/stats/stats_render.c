/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:24:20 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 09:47:43 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fonts.h"

void	render_stats(t_cub3d *cub3d)
{
	t_texture	*item;

	item = get_texture(cub3d, cub3d->player.item);
	render_stats_money(cub3d, item);
	render_stats_health(cub3d, item);
	render_stats_time(cub3d, item);
	igmlx_simple_copy_to_dest(item, cub3d->rendering_buffer, (t_uvec2){SCREEN_W
		- item->width - RIGHT_HUD_OFFSET, RIGHT_HUD_OFFSET});
}
