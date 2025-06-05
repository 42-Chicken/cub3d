/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:02:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/05 09:47:19 by rguigneb         ###   ########.fr       */
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
		if (time - cub3d->damage_screen.time_start > 2000)
		{
			cub3d->damage_screen.time_start = 0;
			cub3d->damage_screen.is_anim = false;
		}
	}
}

void	igmlx_apply_gray_filter(t_cub3d *cub3d, double intensity)
{
	t_uvec2	pos;
	t_color	*pixel;
	t_color	original_color;

	if (!cub3d || !cub3d->rendering_buffer || intensity < 0.0
		|| intensity > 1.0)
		return ;
	pos = (t_uvec2){0, cub3d->rendering_buffer->height / 3};
	while (pos.y < (unsigned int)cub3d->rendering_buffer->height / 1.5)
	{
		pos.x = 0;
		while (pos.x < (unsigned int)cub3d->rendering_buffer->width)
		{
			pixel = get_pixel(cub3d->rendering_buffer, pos);
			if (*pixel != 0xFF000000)
			{
				original_color = *pixel;
				*pixel = igmlx_melt_colors_weigthed(original_color, 0x000000,
						intensity);
			}
			pos.x++;
		}
		pos.y++;
	}
}
void	update_death(t_cub3d *cub3d)
{
	t_img	*img;

	img = get_texture(cub3d, TEXTURE_WASTED);
	if (cub3d->player.health == 0 || cub3d->player.health >= 101)
	{
		cub3d->alive = false;
		cub3d->player.health = 0;
		igmlx_apply_gray_filter(cub3d, 0.65);
		igmlx_simple_copy_to_dest(img, cub3d->rendering_buffer,
			(t_uvec2){SCREEN_W / 2 - 250, SCREEN_H / 2 - 75});
		usleep(5000);
	}
}
void	render_game(t_cub3d *cub3d)
{

	if (cub3d->alive == true)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->rendering_buffer);
		cub3d->rendering_buffer = mlx_new_image(cub3d->mlx, SCREEN_W, SCREEN_H);
		if (!cub3d->rendering_buffer)
			return (end_loop(cub3d),
				_error("failed to create rendering buffer!"));
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
	else
	{
		long time = gettime();
		while (gettime() - time < 3000)
		{
			usleep(10000);
		}
		end_loop(cub3d);
	}
		update_death(cub3d);
}
