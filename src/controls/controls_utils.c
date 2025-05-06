/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:41:05 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 11:42:38 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool is_pressed(t_cub3d *cub3d, int key)
{
	int i;

	i = 0;
	while (i < KEY_PRESSED_MAX)
	{
		if (cub3d->key_pressed[i] == key)
			return (true);
		i++;
	}
	return (false);
}
