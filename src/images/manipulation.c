/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:11:32 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/19 22:05:48 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color	igmlx_melt_colors_weigthed(t_color input, t_color filter, double filter_weight)
{
	t_color	result;
	double	input_weight;

	t_color alpha, red, green, blue;
	t_color f_alpha, f_red, f_green, f_blue;
	input_weight = 1.0 - filter_weight;
	alpha = (input >> 24) & 0xFF;
	red = (input >> 16) & 0xFF;
	green = (input >> 8) & 0xFF;
	blue = input & 0xFF;
	f_alpha = (filter >> 24) & 0xFF;
	f_red = (filter >> 16) & 0xFF;
	f_green = (filter >> 8) & 0xFF;
	f_blue = filter & 0xFF;
	alpha = (alpha * input_weight) + (f_alpha * filter_weight);
	red = (red * input_weight) + (f_red * filter_weight);
	green = (green * input_weight) + (f_green * filter_weight);
	blue = (blue * input_weight) + (f_blue * filter_weight);
	result = ((t_color)alpha << 24) | ((t_color)red << 16) | ((t_color)green << 8) | (t_color)blue;
	return (result);
}

t_color	igmlx_melt_colors(t_color input, t_color filter)
{
	t_color	result;
	double	filter_weight;
	double	input_weight;
	t_argb	rgb1;
	t_argb	rgb2;

	rgb1 = (t_argb){(input >> 24) & 0xFF, (input >> 16) & 0xFF,
		(input >> 8) & 0xFF, input & 0xFF};
	rgb2 = (t_argb){(filter >> 24) & 0xFF, (filter >> 16) & 0xFF,
		(filter >> 8) & 0xFF, filter & 0xFF};
	filter_weight = 0.7;
	input_weight = 1.0 - filter_weight;
	rgb1.alpha = (rgb1.alpha * input_weight) + (rgb2.alpha * filter_weight);
	rgb1.red = (rgb1.red * input_weight) + (rgb2.red * filter_weight);
	rgb1.green = (rgb1.green * input_weight) + (rgb2.green * filter_weight);
	rgb1.blue = (rgb1.blue * input_weight) + (rgb2.blue * filter_weight);
	result = ((t_color)rgb1.alpha << 24) | ((t_color)rgb1.red << 16) | \
	((t_color)rgb1.green << 8) | (t_color)rgb1.blue;
	return (result);
}

void	igmlx_apply_color_filter(t_img *img, t_color filter)
{
	t_uvec2	c;
	t_color	*pixel;

	c = (t_uvec2){-1, -1};
	while (++c.x < (unsigned int)img->width)
	{
		c.y = -1;
		while (++c.y < (unsigned int)img->height)
		{
			pixel = get_pixel(img, c);
			if (*pixel != 0xFF000000)
				*pixel = igmlx_melt_colors(*pixel, filter);
		}
	}
}

void	igmlx_copy_to_dest(t_img_pos origin, t_uvec2 length, t_img_pos dest,
		bool transparancy)
{
	t_uvec2	c;
	t_color	*dest_pixel;
	t_color	*origin_pixel;

	c = (t_uvec2){-1, -1};
	while (++c.x < length.x)
	{
		c.y = -1;
		while (++c.y < length.y)
		{
			origin_pixel = get_pixel(origin.img, (t_uvec2){origin.pos.x + c.x,
					origin.pos.y + c.y});
			dest_pixel = get_pixel(dest.img, (t_uvec2){dest.pos.x + c.x,
					dest.pos.y + c.y});
			if (transparancy && *origin_pixel != 0xFF000000)
				*dest_pixel = *origin_pixel;
			else if (!transparancy)
				*dest_pixel = *origin_pixel;
		}
	}
}

void	igmlx_simple_copy_to_dest(t_img *origin, t_img *dest, t_uvec2 dest_pos)
{
	t_uvec2	c;
	t_color	*dest_pixel;
	t_color	*origin_pixel;

	c = (t_uvec2){-1, -1};
	while (++c.x < (unsigned int)origin->width)
	{
		c.y = -1;
		while (++c.y < (unsigned int)origin->height)
		{
			origin_pixel = get_pixel(origin, (t_uvec2){c.x, c.y});
			dest_pixel = get_pixel(dest, (t_uvec2){dest_pos.x + c.x, dest_pos.y
					+ c.y});
			if (*origin_pixel != 0xFF000000)
				*dest_pixel = *origin_pixel;
		}
	}
}
