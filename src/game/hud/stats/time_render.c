/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 08:42:49 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/02 09:13:22 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SEC_PER_DAY 86400
#define SEC_PER_HOUR 3600
#define SEC_PER_MIN 60

void	render_stats_time(t_cub3d *cub3d, t_texture *item)
{
	t_time	time;
	char	time_str[6];
	long	hms;
	int		hour;
	int		min;

	ft_memset(&time_str, '0', 5);
	gettimeofday(&time, NULL);
	hms = (time.tv_sec % SEC_PER_DAY);
	hour = (hms / SEC_PER_HOUR) + 2;
	min = (hms % SEC_PER_HOUR) / SEC_PER_MIN;
	if (hour < 10)
		custom_itoa(hour, (char *)&time_str + 1);
	else
		custom_itoa(hour, (char *)&time_str);
	time_str[2] = ':';
	if (min < 10)
		custom_itoa(min, (char *)&time_str + 4);
	else
		custom_itoa(min, (char *)&time_str + 3);
	render_text(cub3d, GTA_FONT_YELLOW_NAME, time_str, (t_uvec2){SCREEN_W
		- item->width - RIGHT_HUD_OFFSET * 2.2 - 5 * 18, item->height
		- RIGHT_HUD_OFFSET - 80});
}
