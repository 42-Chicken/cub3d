/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:39:11 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/16 09:27:04 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	*loading_thread_routine(void *data)
// {
// 	t_cub3d	*cub3d;
// 	int		i;
// 	t_img	*loading;

// 	cub3d = (t_cub3d *)data;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&cub3d->mutex);
// 		if (cub3d->mlx && cub3d->win)
// 		{
// 			pthread_mutex_unlock(&cub3d->mutex);
// 			usleep(10000);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&cub3d->mutex);
// 	}
// 	pthread_mutex_lock(&cub3d->mutex);
// 	cub3d->rendering_buffer = mlx_new_image(cub3d->mlx, SCREEN_W, SCREEN_H);
// 	if (!cub3d->rendering_buffer)
// 		return (NULL);
// 	loading = mlx_xpm_file_to_image(cub3d->mlx, "assets/loading_screens/1.xpm",
// 			&i, &i);
// 	mlx_put_image_to_window(cub3d->mlx, cub3d->win, loading, 0, 0);
// 	pthread_mutex_unlock(&cub3d->mutex);
// 	while (r_size_t(&cub3d->mutex,
// 			&cub3d->textures_loaded) < __TEXTURES_COUNT__)
// 	{
// 		// printf("laoded : %ld\n", r_size_t(&cub3d->mutex,
// 		// 		&cub3d->textures_loaded));
// 	}
// 	_debug("Loading thread finished");
// 	return (NULL);
// }

// bool	init_loading_thread(t_cub3d *cub3d)
// {
// 	(void)cub3d;
// 	pthread_mutex_init(&cub3d->mutex, NULL);
// 	if (pthread_create(&cub3d->loading_thread, NULL, loading_thread_routine,
// 			cub3d) == -1)
// 		return (_error("failed to create the loading thread !"), true);
// 	return (false);
// }
