/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:26:12 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/24 09:49:00 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parsing_is_correct_file_path(t_cub3d *cub3d)
{
	const char	*path;

	path = cub3d->av[1];
	if (path == NULL || endswith((char *)path, (char *)".cub") == false
		|| endswith((char *)path, (char *)"/.cub") == true)
		return (_error("please provide a valid map path, \
only <.cub> maps are supported!"),
				false);
	return (true);
}

int	parsing_open_file(t_cub3d *cub3d)
{
	const char	*path;
	int			fd;

	path = cub3d->av[1];
	fd = open(path, O_RDONLY);
	return (fd);
}
