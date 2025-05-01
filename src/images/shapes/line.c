/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:45:42 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 10:00:18 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_locations(t_vec2 start, t_vec2 end)
{
	t_vec2	tmp;

	if (end.y < 0 && abs((int)end.y - (int)start.y) > abs((int)end.x
			- (int)start.x))
	{
		tmp = start;
		start = end;
		end = tmp;
	}
}

void	draw_line(t_img *buffer, int color, t_vec2 start, t_vec2 end)
{
	t_dvec2	distance;
	double	step_value;
	t_dvec2	step;
	int		i;
	t_vec2	c;

	i = 0;
	rotate_locations(start, end);
	distance.x = end.x - start.x;
	distance.y = end.y - start.y;
	step_value = fmax(fabs(distance.x), fabs(distance.y));
	if (step_value != 0)
	{
		step.x = distance.x / step_value;
		step.y = distance.y / step_value;
	}
	while (i <= step_value + 1)
	{
		c.x = floor(start.x + i * step.x);
		c.y = floor(start.y + i * step.y);
		put_pixel_to_buffer(buffer, (t_uvec2){c.x, c.y}, color);
		i++;
	}
}
