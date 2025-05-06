/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:51:45 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 09:22:37 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fonts.h"

void	render_text(t_cub3d *cub3d, char *font_name, char *text, t_uvec2 pos)
{
	igmlx_put_str_to_buffer(get_font(cub3d, GTA_FONT_BLACK_NAME), text,
		cub3d->rendering_buffer, (t_uvec2){pos.x + 2, pos.y + 2});
	igmlx_put_str_to_buffer(get_font(cub3d, font_name), text,
		cub3d->rendering_buffer, pos);
}
