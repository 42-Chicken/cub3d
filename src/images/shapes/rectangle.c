/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:09 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/29 11:28:18 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect(t_img *buffer, int color, t_uvec2 start, t_uvec2 end)
{
	t_uvec2	tmp;

	tmp = start;
	while (tmp.x < end.x)
	{
		tmp.y = start.y;
		while (tmp.y < end.y)
		{
			put_pixel_to_buffer(buffer, tmp, color);
			tmp.y++;
		}
		tmp.x++;
	}
	}
