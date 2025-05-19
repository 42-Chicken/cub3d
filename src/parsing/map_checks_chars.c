/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:49:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/19 17:33:08 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	parsing_is_part_of_map_chars(char c)
{
	if (ft_strchr(MAP_SUPPORTED_CHARS, c) || ft_isspace(c)
		|| parsing_is_player(c) || c == CUB3D_MAP_VOID)
		return (true);
	return (false);
}

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
			if (!parsing_is_part_of_map_chars(cub3d->map.buffer[y][x]))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}
