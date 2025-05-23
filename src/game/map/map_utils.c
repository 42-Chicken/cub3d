/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:04:50 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 09:49:12 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	map_is_outside_map_buffer(t_cub3d *cub3d, size_t x, size_t y)
{
	return (!cub3d->map.buffer || x < 0 || y < 0 || y >= cub3d->map.height
		|| x >= ft_strlen(cub3d->map.buffer[y]));
}

bool	map_is_floor(t_cub3d *cub3d, size_t x, size_t y)
{
	char	type;

	if (map_is_outside_map_buffer(cub3d, x, y))
		return (false);
	type = cub3d->map.buffer[y][x];
	return (type == CUB3D_MAP_FLOOR);
}

bool	map_is_wall(t_cub3d *cub3d, size_t x, size_t y)
{
	char	type;

	if (map_is_outside_map_buffer(cub3d, x, y))
		return (false);
	type = cub3d->map.buffer[y][x];
	return (type != CUB3D_MAP_FLOOR);
}

char	map_get_wall(t_cub3d *cub3d, size_t x, size_t y)
{
	char	type;

	if (map_is_outside_map_buffer(cub3d, x, y))
		return (false);
	type = cub3d->map.buffer[y][x];
	return (type);
}

bool	map_is_void(t_cub3d *cub3d, size_t x, size_t y)
{
	char	type;

	if (map_is_outside_map_buffer(cub3d, x, y))
		return (true);
	type = cub3d->map.buffer[y][x];
	return (type == CUB3D_MAP_VOID);
}
