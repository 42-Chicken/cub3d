/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:55:38 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/28 09:19:55 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parsing_map_only_contains_allowed_chars(t_cub3d *cub3d)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < cub3d->map.height)
	{
		x = 0;
		while (x < ft_strlen(cub3d->map.buffer[y]))
		{
			if (!ft_strchr(SPACES CUB3D_MAP_SUPPORTED_CHARS,
					cub3d->map.buffer[y][x])
				&& cub3d->map.buffer[y][x] != CUB3D_MAP_VOID)
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	parsing_duplicates_player_data(t_cub3d *cub3d)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < cub3d->map.height)
	{
		x = 0;
		while (x < ft_strlen(cub3d->map.buffer[y]))
		{
			if (ft_strchr("NSEW", cub3d->map.buffer[y][x])
				&& cub3d->player.position.x != x
				&& cub3d->player.position.y != y)
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	parsing_is_neighbor_void(t_cub3d *cub3d, size_t x, size_t y)
{
	return (
		map_is_void(cub3d, x + 1, y) == true
		|| map_is_void(cub3d, x - 1, y) == true
		|| map_is_void(cub3d, x, y + 1) == true
		|| map_is_void(cub3d, x, y - 1) == true
	);
}

bool	parsing_check_if_map_is_enclosed(t_cub3d *cub3d)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < cub3d->map.height)
	{
		x = 0;
		while (x < ft_strlen(cub3d->map.buffer[y]))
		{
			if (map_is_floor(cub3d, x, y) == true
				&& parsing_is_neighbor_void(cub3d, x, y))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	parsing_check_map(t_cub3d *cub3d)
{
	if (parsing_map_only_contains_allowed_chars(cub3d) == false)
		return (_error("none supported characteres in map data!"), false);
	if (parsing_duplicates_player_data(cub3d) == false)
		return (_error("multiples player spawn point in map data!"), false);
	if (parsing_check_if_map_is_enclosed(cub3d) == false)
		return (_error("map is not enclosed correcly!"), false);
	// check walls
	return (true);
}
