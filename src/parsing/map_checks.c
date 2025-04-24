/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:55:38 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/24 15:06:30 by rguigneb         ###   ########.fr       */
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
					cub3d->map.buffer[y][x]))
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
	return (true);
}
