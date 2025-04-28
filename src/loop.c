/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:37:33 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/28 15:50:44 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void end_loop(t_cub3d *cub3d)
{
	_info("closed !");
	mlx_loop_end(cub3d->mlx);
}

void loop(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx, cub3d->rendering_buffer);
	cub3d->rendering_buffer = mlx_new_image(cub3d->mlx, SCREEN_W, SCREEN_H);
	if (!cub3d->rendering_buffer)
		return (end_loop(cub3d), _error("failed to create rendering buffer!"));
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer, 0, 0);
}
