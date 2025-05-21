/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:20:50 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/21 10:07:12 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(t_cub3d *data, t_ray *ray, double height, double begin)
{
	size_t	y;

	y = (int)height + begin;
	while (y < SCREEN_H)
	{
		put_pixel_to_buffer(data->rendering_buffer, (t_uvec2){ray->x, y},
			0xFF0000);
		y++;
	}
}
