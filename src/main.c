/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:08:17 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/06 10:26:29 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_average_fps(t_cub3d *cub3d)
{
	struct timeval	end_time;
	double			start_sec;
	double			end_sec;
	double			elapsed;
	double			avg_fps;

	gettimeofday(&end_time, NULL);
	start_sec = cub3d->start_time.tv_sec + cub3d->start_time.tv_usec / 1e6;
	end_sec = end_time.tv_sec + end_time.tv_usec / 1e6;
	elapsed = end_sec - start_sec;
	if (elapsed > 0)
	{
		avg_fps = cub3d->tick / elapsed;
		printf("Average FPS: %.2f\n", avg_fps);
	}
	else
	{
		printf("Elapsed time too small to compute FPS.\n");
	}
}

void	init_data(t_cub3d *cub3d)
{
	ft_bzero(cub3d, sizeof(t_cub3d));
	cub3d->menu = CUB3D_MENU_NONE;
	cub3d->settings.fov = 60;
	cub3d->settings.mouse_sens = 5;
	cub3d->player.item = TEXTURE_HUD_PISTOL;
	cub3d->player.health = 100;
	cub3d->key_pressed_index = 0;
	cub3d->settings.player_speed = 3;
	cub3d->settings.player_rotation_speed = 4;
	cub3d->alive = true;
}

int	main(int argc, char const *argv[])
{
	t_cub3d	cub3d;

	init_data(&cub3d);
	cub3d.ac = argc;
	cub3d.av = argv;
	if (parse(&cub3d) == false)
		return (free_all_contexts_garbage(), EXIT_FAILURE);
	if (init_mlx(&cub3d) == false)
		return (free_all_contexts_garbage(), EXIT_FAILURE);
	init_menus(&cub3d);
	init_settings(&cub3d);
	init_mlx_hooks(&cub3d);
	cub3d.loaded = true;
	gettimeofday(&cub3d.start_time, NULL);
	controls_setup_mouse(&cub3d);
	mlx_loop(cub3d.mlx);
	controls_pause_mouse(&cub3d);
	print_average_fps(&cub3d);
	destroy_mlx(&cub3d);
	free_all_contexts_garbage();
	return (EXIT_SUCCESS);
}
