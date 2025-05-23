/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:24:10 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 14:41:30 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sky(t_cub3d *data, t_ray *ray, double begin)
{
	size_t	y;

	y = 0;
	while (y < begin)
	{
		put_pixel_to_buffer(data->rendering_buffer, (t_uvec2){ray->x, y},
			0x120228);
		y++;
	}
}
