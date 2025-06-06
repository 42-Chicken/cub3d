/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:06:21 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/06 10:06:26 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2	get_draw_width(t_entity *entity, int x)
{
	t_vec2	draw_x;

	draw_x.x = x - entity->width / 2;
	if (draw_x.x < 0)
		draw_x.x = 0;
	draw_x.y = x + entity->width / 2;
	if (draw_x.y >= SCREEN_W)
		draw_x.y = SCREEN_W - 1;
	return (draw_x);
}

t_vec2	get_draw_height(t_entity *entity)
{
	t_vec2	draw_y;

	draw_y.x = -entity->height / 2 + SCREEN_H / 2 + entity->y_offset;
	if (draw_y.x < 0)
		draw_y.x = 0;
	draw_y.y = entity->height / 2 + SCREEN_H / 2 + entity->y_offset;
	if (draw_y.y >= SCREEN_H)
		draw_y.y = SCREEN_H - 1;
	return (draw_y);
}

t_vec2	calculate_width_height_and_draw(t_cub3d *cub3d, t_entity *entity,
		t_vec2 *draw_height, int x)
{
	entity->width = fabs(entity->scale.x * cub3d->distance_from_camera
			/ entity->transformed.y);
	entity->height = fabs(entity->scale.y * cub3d->distance_from_camera
			/ entity->transformed.y);
	*draw_height = get_draw_height(entity);
	return (get_draw_width(entity, x));
}
