/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:12:20 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 09:48:47 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fonts.h"

static void	init_letters_images(t_cub3d *igmlx, t_igmlx_font *font,
		t_img *font_img)
{
	char	c;
	int		y;
	int		x;
	t_img	*tmp;

	c = -1;
	y = 0;
	x = 0;
	while (++c < CHAR_MAX)
	{
		tmp = mlx_new_image(igmlx->mlx, 48, 48);
		if (!tmp)
			return (_error("mlx_new_image failed!"), (void)0);
		if (x == 16)
		{
			y++;
			x = 0;
		}
		igmlx_copy_to_dest((t_img_pos){font_img, (t_uvec2){x * 48, y * 48}},
			(t_uvec2){48, 48}, (t_img_pos){tmp, (t_uvec2){0, 0}}, false);
		igmlx_apply_color_filter(tmp, font->color);
		font->letters[(int)c] = tmp;
		x++;
	}
}

void	igmlx_load_font(t_cub3d *igmlx, char *path, char *name,
		t_igmlx_font_params params)
{
	t_igmlx_font	*font;
	t_img			*img;

	if (!path || !name)
		return ;
	if (get_font(igmlx, name))
	{
		_warning("tried to load the same font twice!");
		return ;
	}
	font = balloc(sizeof(t_igmlx_font));
	if (!font)
		return ;
	font->color = params.color;
	font->size_mutliplier = params.size_multiplier;
	font->inner_offset = params.inner_offset;
	font->path = path;
	font->name = name;
	img = mlx_xpm_file_to_image(igmlx->mlx, path, (int *)&font->length.x,
			(int *)&font->length.y);
	if (!img)
		return (_error("failed to load xpm file of a font"), (void)0);
	init_letters_images(igmlx, font, img);
	mlx_destroy_image(igmlx->mlx, img);
	ft_lstadd_front(&igmlx->fonts, ft_lstnew(font));
}
