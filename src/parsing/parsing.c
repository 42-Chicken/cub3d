/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:13:08 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/24 14:27:51 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse(t_cub3d *cub3d)
{
	int	fd;

	create_safe_memory_context();
	if (cub3d->ac <= 1 || cub3d->ac > 2)
		return (exit_safe_memory_context(), _error("usage : ./cub3d <map.ber>"),
			false);
	if (parsing_is_correct_file_path(cub3d) == false)
		return (exit_safe_memory_context(), false);
	fd = parsing_open_file(cub3d);
	if (fd == -1)
		return (exit_safe_memory_context(), _error("cannot open map file!"),
			false);
	if (parse_data(cub3d, fd) == false)
		return (exit_safe_memory_context(), close(fd), false);
	if (!cub3d->east_texture_path || !cub3d->west_texture_path
		|| !cub3d->north_texture_path || !cub3d->south_texture_path)
		return (exit_safe_memory_context(), close(fd),
			_error("map data is not complete!"), false);
	if (parse_map(cub3d, fd) == false)
		return (exit_safe_memory_context(), close(fd), false);
	return (close(fd), exit_safe_memory_context(), true);
}
