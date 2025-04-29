/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:08:17 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/29 12:41:43 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char const *argv[])
{
	t_cub3d	cub3d;

	ft_bzero(&cub3d, sizeof(t_cub3d));
	cub3d.ac = argc;
	cub3d.av = argv;
	if (parse(&cub3d) == false)
		return (free_all_contexts_garbage(), EXIT_FAILURE);
	if (init_mlx(&cub3d) == false)
		return (free_all_contexts_garbage(), EXIT_FAILURE);
	printf("F %x \n", cub3d.floor_color);
	printf("C %x \n", cub3d.ceiling_color);
	printf("NO %s \n", cub3d.north_texture_path);
	printf("SO %s \n", cub3d.south_texture_path);
	printf("WE %s \n", cub3d.west_texture_path);
	printf("EA %s \n", cub3d.east_texture_path);
	printf("MAP width %zu \n", cub3d.map.width);
	printf("MAP height %zu \n", cub3d.map.height);
	init_mlx_hooks(&cub3d);
	mlx_loop(cub3d.mlx);
	destroy_mlx(&cub3d);
	free_all_contexts_garbage();
	return (EXIT_SUCCESS);
}
