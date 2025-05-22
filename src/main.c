/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:08:17 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/22 08:30:28 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_average_fps(t_cub3d *cub3d)
{
	struct timeval end_time;
	gettimeofday(&end_time, NULL);

	double start_sec = cub3d->start_time.tv_sec + cub3d->start_time.tv_usec / 1e6;
	double end_sec = end_time.tv_sec + end_time.tv_usec / 1e6;
	double elapsed = end_sec - start_sec;

	if (elapsed > 0)
	{
		double avg_fps = cub3d->tick / elapsed;
		printf("Average FPS: %.2f\n", avg_fps);
	}
	else
	{
		printf("Elapsed time too small to compute FPS.\n");
	}
}
// day night cycle

int	main(int argc, char const *argv[])
{
	t_cub3d	cub3d;

	ft_bzero(&cub3d, sizeof(t_cub3d));
	cub3d.ac = argc;
	cub3d.av = argv;
	cub3d.menu = CUB3D_MENU_NONE;
	cub3d.settings.fov = 60;
	cub3d.settings.mouse_sens = 5;
	cub3d.player.item = TEXTURE_HUD_PISTOL;
	cub3d.player.health = 100;
	cub3d.key_pressed_index = 0;
	cub3d.settings.player_speed = 1;
	cub3d.settings.player_rotation_speed = 4;
	if (parse(&cub3d) == false)
		return (free_all_contexts_garbage(), EXIT_FAILURE);
	if (init_mlx(&cub3d) == false)
		return (free_all_contexts_garbage(), EXIT_FAILURE);
	init_menus(&cub3d);
	printf("F %x \n", cub3d.floor_color);
	printf("C %x \n", cub3d.ceiling_color);
	printf("NO %s \n", cub3d.north_texture_path);
	printf("SO %s \n", cub3d.south_texture_path);
	printf("WE %s \n", cub3d.west_texture_path);
	printf("EA %s \n", cub3d.east_texture_path);
	printf("MAP width %zu \n", cub3d.map.width);
	printf("MAP height %zu \n", cub3d.map.height);
	init_mlx_hooks(&cub3d);
	cub3d.loaded = true;
	gettimeofday(&cub3d.start_time, NULL);
	mlx_loop(cub3d.mlx);
	print_average_fps(&cub3d);
	destroy_mlx(&cub3d);
	free_all_contexts_garbage();
	return (EXIT_SUCCESS);
}
