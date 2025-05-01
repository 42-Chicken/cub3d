/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:24:12 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 12:30:48 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dvec2	normalize_vector(t_dvec2 vec)
{
	double	magnitude;

	magnitude = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (magnitude != 0)
	{
		vec.x /= magnitude;
		vec.y /= magnitude;
	}
	return (vec);
}
