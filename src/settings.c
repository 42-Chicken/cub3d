/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:09:06 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/22 12:14:01 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_settings(t_cub3d *cub3d)
{
	cub3d->fov = cub3d->settings.fov * (M_PI / 180);
	cub3d->distance_from_camera = (double)((SCREEN_W / 2) / tan(cub3d->fov
				/ 2));
	cub3d->plane_len = tan(cub3d->fov * 0.5);
	cub3d->num_rays = ((int)SCREEN_W / (int)RAYS);
}
