/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_to_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:07:13 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/30 10:58:27 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_buffer(t_img *buffer, t_uvec2 pos, t_color color)
{
	if (pos.x < 0)
		pos.x = 0;
	if (pos.x > (unsigned int)buffer->width)
		pos.x = (unsigned int)buffer->width;
	if (pos.y < 0)
		pos.y = 0;
	if (pos.y > (unsigned int)buffer->height)
		pos.y = (unsigned int)buffer->height;
	((t_color *)buffer->data)[(pos.y * (buffer->size_line / 4))
		+ pos.x] = color;
}
