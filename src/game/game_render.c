/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:02:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/03 17:22:24 by efranco          ###   ########.fr       */
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
static t_color	color_to_grayscale(t_color color)
{
	t_argb	rgb;
	t_color	gray_value;

	rgb = (t_argb){(color >> 24) & 0xFF, (color >> 16) & 0xFF,
		(color >> 8) & 0xFF, color & 0xFF};
	gray_value = (t_color)(0.299 * rgb.red + 0.587 * rgb.green + 0.114
			* rgb.blue);
	return (((t_color)rgb.alpha << 24) | (gray_value << 16) | (gray_value << 8) | gray_value);
}
void	igmlx_apply_gray_filter(t_cub3d *cub3d, double intensity)
{
	t_uvec2	pos;
	t_color	*pixel;
	t_color	gray_color;
	t_color	original_color;

	if (!cub3d || !cub3d->rendering_buffer || intensity < 0.0
		|| intensity > 1.0)
		return ;
	pos = (t_uvec2){0, 0};
	while (pos.y < (unsigned int)cub3d->rendering_buffer->height)
	{
		pos.x = 0;
		while (pos.x < (unsigned int)cub3d->rendering_buffer->width)
		{
			pixel = get_pixel(cub3d->rendering_buffer, pos);
			if (*pixel != 0xFF000000)
			{
				original_color = *pixel;
				gray_color = color_to_grayscale(original_color);
				*pixel = igmlx_melt_colors_weigthed(original_color, gray_color,
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
		igmlx_simple_copy_to_dest(img, cub3d->rendering_buffer,
			(t_uvec2){SCREEN_W / 2 - 250, SCREEN_H / 2 - 100});
		igmlx_apply_gray_filter(cub3d, 0.5);
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
		exit(EXIT_SUCCESS);
	}
		update_death(cub3d);
}
