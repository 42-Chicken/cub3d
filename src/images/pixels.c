/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:48:12 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 09:48:25 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// maybe can be optimized, check igmxl_copy...
t_color	*get_pixel(t_img *img, t_uvec2 pos)
{
	if (pos.x >= (unsigned int)img->width)
		pos.x = img->width;
	if (pos.y >= (unsigned int)img->height)
		pos.y = img->height;
	return ((t_color *)img->data + pos.y * (img->size_line / 4) + pos.x);
}

t_color	get_pixel_color(t_img *img, t_uvec2 pos)
{
	return (*get_pixel(img, pos));
}
