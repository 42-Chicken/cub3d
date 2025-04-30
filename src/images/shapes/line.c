/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:45:42 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/30 14:58:14 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_img *buffer, int color, t_vec2 start, t_vec2 end)
{
	double		distance_x;
	double		distance_y;
	double		step;
	double		stepX;
	double		stepY;
	int			i;
	t_vec2	tmp;
	int			y;
	int			x;

	i = 0;
	if (end.y < 0 && abs((int)end.y - (int)start.y) > abs((int)end.x - (int)start.x))
	{
		tmp = start;
		start = end;
		end = tmp;
	}
	distance_x = end.x - start.x;
	distance_y = end.y - start.y;
	step = fmax(fabs(distance_x), fabs(distance_y));
	if (step != 0)
	{
		stepX = distance_x / step;
		stepY = distance_y / step;
	}
	while (i <= step + 1)
	{
		y = floor(start.y + i * stepY);
		x = floor(start.x + i * stepX);
		put_pixel_to_buffer(buffer, (t_uvec2){x, y}, color);
		i++;
	}
}
