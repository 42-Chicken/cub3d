/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:51:45 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 15:53:51 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fonts.h"

void	render_text(t_cub3d *cub3d, char *font_name, char *text, t_uvec2 pos)
{
	igmlx_put_str_to_buffer(cub3d, text, GTA_FONT_BLACK_NAME,
		cub3d->rendering_buffer, (t_uvec2){pos.x + 2, pos.y + 2});
	igmlx_put_str_to_buffer(cub3d, text, font_name,
		cub3d->rendering_buffer, pos);
}
