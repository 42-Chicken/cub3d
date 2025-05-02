/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:12:30 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/02 10:12:36 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	fast_is_between(t_vec2 pos, t_vec2 bpos1, t_vec2 bpos2)
{
	return (pos.x >= bpos1.x && pos.x <= bpos2.x && pos.y >= bpos1.y
		&& pos.y <= bpos2.y);
}
