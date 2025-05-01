/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:24:20 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 16:57:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fonts.h"

void	render_stats(t_cub3d *cub3d)
{
	render_stats_money(cub3d);

	t_texture *item;

	item = get_texture(cub3d, cub3d->player.item);
	igmlx_simple_copy_to_dest_ignore_null(item, cub3d->rendering_buffer, (t_uvec2){SCREEN_W - item->width - 25, 25});
}
