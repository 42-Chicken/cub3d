/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:17:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/06/06 10:19:31 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_hud(t_cub3d *cub3d)
{
	render_hand(cub3d);
	render_minimap(cub3d);
	render_stats(cub3d);
}
