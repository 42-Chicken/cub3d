/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:02:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 10:07:32 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_game(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx, cub3d->rendering_buffer);
	cub3d->rendering_buffer = mlx_new_image(cub3d->mlx, SCREEN_W, SCREEN_H);
	if (!cub3d->rendering_buffer)
		return (end_loop(cub3d), _error("failed to create rendering buffer!"));
	handle_player_movement(cub3d);
	draw_rect(cub3d->rendering_buffer, cub3d->floor_color, (t_uvec2){0, 0},
		(t_uvec2){SCREEN_W, SCREEN_H});
	render_minimap(cub3d);
	render_stats(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer,
		0, 0);
}
