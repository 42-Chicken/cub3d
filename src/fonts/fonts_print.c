/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:04:27 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 09:48:51 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fonts.h"

void	igmlx_put_str_to_buffer(t_igmlx_font *font, char *str, t_img *buffer,
		t_uvec2 pos)
{
	int	i;
	int	y;

	y = 0;
	i = -1;
	if (!font)
		return (_warning("tried to print with unknown font!"), (void)0);
	while (str[++i])
	{
		if (str[i] == '1')
			font->inner_offset.x += 2;
		if (i == 0)
			igmlx_copy_to_dest((t_img_pos){font->letters[(int)str[i]],
				(t_uvec2){0, 0}}, (t_uvec2){48, 48}, (t_img_pos){buffer,
				(t_uvec2){pos.x + (48 * i), pos.y + (y * 48)}}, true);
		else
			igmlx_copy_to_dest((t_img_pos){font->letters[(int)str[i]],
				(t_uvec2){0, 0}}, (t_uvec2){48, 48}, (t_img_pos){buffer,
				(t_uvec2){pos.x + (48 * i) - font->inner_offset.x * i, pos.y
				+ (y * 48)}}, true);
		if (str[i] == '1')
			font->inner_offset.x -= 2;
	}
}

// if (str[i] == '\n')
// {
// 	y++;
// 	continue ;
// }
