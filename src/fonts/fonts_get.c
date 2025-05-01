/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:05:50 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 14:56:16 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fonts.h"

static bool	is_searched_font(t_igmlx_font *font, char *name)
{
	return (ft_strlen(name) == ft_strlen(font->name) && ft_strncmp(font->name,
			name, ft_strlen(name)) == 0);
}

t_igmlx_font	*get_font(t_cub3d *igmlx, char *name)
{
	t_list	*lst;

	lst = ft_lstget(igmlx->fonts, (bool (*)(void *, void *))is_searched_font,
			name);
	if (!lst)
		return (NULL);
	return ((t_igmlx_font *)lst->content);
}
