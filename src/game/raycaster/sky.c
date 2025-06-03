/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:24:10 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/03 12:09:08 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sky(t_cub3d *data, t_ray *ray, double begin)
{
	size_t	y;
	t_color color;
	t_texture *texture;

	y = 0;
	texture = get_texture(data, TEXTURE_SKY);
	while (y < begin)
	{
		color = get_pixel_color(texture, (t_uvec2){((int)((float)ray->x + (data->player.rotation_angle * 900)) % texture->width), y});
		put_pixel_to_buffer(data->rendering_buffer, (t_uvec2){ray->x, y}, (int)color);
		y++;
	}
}
