/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:02:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/03 15:50:19 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_rendering_buffer(t_cub3d *cub3d)
{
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->rendering_buffer, 0,
		0);
}
void	update_damage(t_cub3d *cub3d)
{
	t_img	*img;
	long	time;

	time = gettime();
	img = get_texture(cub3d, TEXTURE_DAMAGE);
	if (cub3d->damage_screen.is_anim == true)
	{
		igmlx_simple_copy_to_dest(img, cub3d->rendering_buffer, (t_uvec2){0,
			0});
		if (cub3d->damage_screen.time_start - time > 1000)
		{
			printf ("ici\n");
			cub3d->damage_screen.time_start = 0;
			cub3d->damage_screen.is_anim = false;
		}
	}
}
void	render_game(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx, cub3d->rendering_buffer);
	cub3d->rendering_buffer = mlx_new_image(cub3d->mlx, SCREEN_W, SCREEN_H);
	if (!cub3d->rendering_buffer)
		return (end_loop(cub3d), _error("failed to create rendering buffer!"));
	update_player(cub3d);
	update_entities(cub3d);
	render_raycasting(cub3d);
	render_entities(cub3d);
	render_hand(cub3d);
	render_minimap(cub3d);
	render_stats(cub3d);
	render_rendering_buffer(cub3d);
	update_damage(cub3d);
}
