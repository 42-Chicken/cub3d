/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_between.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:32:35 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/21 12:12:55 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	distance_between(t_dvec2 vec1, t_dvec2 vec2)
{
	double	mx;
	double	my;

	mx = vec2.x - vec1.x;
	my = vec2.y - vec1.y;
	return (sqrt(mx * mx + my * my));
}
