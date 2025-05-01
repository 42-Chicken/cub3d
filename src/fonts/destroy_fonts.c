/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_fonts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 08:57:27 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 16:59:55 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fonts.h"

static void	free_font(t_cub3d *igmlx, t_igmlx_font *font)
{
	char	c;

	c = 0;
	while (c < CHAR_MAX)
		if (font->letters[(int)c])
			mlx_destroy_image(igmlx->mlx, font->letters[(int)c++]);
}

void	igmlx_destroy_fonts_list(t_cub3d *igmlx, t_list **fonts)
{
	t_list	*current;
	t_list	*tmp;

	if (!fonts)
		return ;
	current = *fonts;
	while (current)
	{
		tmp = current->next;
		if (current->content)
			free_font(igmlx, current->content);
		current = tmp;
	}
}
