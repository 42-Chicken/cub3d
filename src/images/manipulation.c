/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:11:32 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 10:15:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// maybe can be optimized, check igmxl_copy...
t_color	*get_pixel(t_img *img, t_uvec2 pos)
{
	if (pos.x >= (unsigned int)img->width)
		pos.x = img->width;
	if (pos.y >= (unsigned int)img->height)
		pos.y = img->height;
	return ((t_color *)img->data + pos.y * (img->size_line / 4) + pos.x);
}

t_color	get_pixel_color(t_img *img, t_uvec2 pos)
{
	return (*get_pixel(img, pos));
}

t_color	igmlx_melt_colors(t_color input, t_color filter)
{
	t_color	result;
	double	filter_weight;
	double	input_weight;
	t_color alpha, red, green, blue;
	t_color f_alpha, f_red, f_green, f_blue;

	filter_weight = 0.7;
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

void	igmlx_copy_to_dest(t_img *origin, t_uvec2 origin_pos, t_uvec2 length,
		t_img *dest, t_uvec2 dest_pos)
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
			dest_pixel = get_pixel(dest, (t_uvec2){dest_pos.x + c.x, dest_pos.y
					+ c.y});
			origin_pixel = get_pixel(origin, (t_uvec2){origin_pos.x + c.x,
					origin_pos.y + c.y});
			*dest_pixel = *origin_pixel;
		}
	}
}

void	igmlx_copy_to_dest_ignore_null(t_img *origin, t_uvec2 origin_pos,
		t_uvec2 length, t_img *dest, t_uvec2 dest_pos)
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
			origin_pixel = get_pixel(origin, (t_uvec2){origin_pos.x + c.x,
					origin_pos.y + c.y});
			dest_pixel = get_pixel(dest, (t_uvec2){dest_pos.x + c.x, dest_pos.y
					+ c.y});
			if (*origin_pixel != 0xFF000000)
				*dest_pixel = *origin_pixel;
		}
	}
}

void	igmlx_simple_copy_to_dest_ignore_null(t_img *origin, t_img *dest,
		t_uvec2 dest_pos)
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

void	igmlx_set_to_null(t_img *origin, t_uvec2 origin_pos, t_uvec2 length)
{
	t_uvec2	c;

	c = (t_uvec2){-1, -1};
	while (++c.x < length.x)
	{
		c.y = -1;
		while (++c.y < length.y)
		{
			*get_pixel(origin, (t_uvec2){origin_pos.x + c.x, origin_pos.y
					+ c.y}) = 0xFF000000;
		}
	}
}
