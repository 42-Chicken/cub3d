/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:57:47 by efranco           #+#    #+#             */
/*   Updated: 2025/05/19 23:01:54 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	load_animation(t_cub3d *data)
{
	data->animation[HAND].img[0] = TEXTURE_PUNCH1;
	data->animation[HAND].img[1] = TEXTURE_PUNCH2;
	data->animation[HAND].img[2] = TEXTURE_PUNCH3;
	data->animation[GUN].img[0] = TEXTURE_PISTOL1;
	data->animation[GUN].img[1] = TEXTURE_PISTOL2;
	data->animation[GUN].img[2] = TEXTURE_PISTOL3;
	data->animation[GUN].img[3] = TEXTURE_PISTOL4;
	data->animation[GUN].img[4] = TEXTURE_PISTOL5;
	data->animation[SHOTGUN].img[0] = TEXTURE_SHOTGUN1;
	data->animation[SHOTGUN].img[1] = TEXTURE_SHOTGUN2;
	data->animation[SHOTGUN].img[2] = TEXTURE_SHOTGUN3;
	data->animation[SHOTGUN].img[3] = TEXTURE_SHOTGUN4;
	data->animation[SHOTGUN].img[4] = TEXTURE_SHOTGUN5;
	data->animation[HAND].time_start = 0;
	data->animation[GUN].time_start = 0;
	data->animation[SHOTGUN].time_start = 0;
}
void	render_hand(t_cub3d *data)
{
	static int i = 0;
	static int j = 0;
	if (data->animation[HAND + j].time_start == 0)
		data->animation[HAND + j].time_start = gettime();

	if (gettime() - data->animation[HAND + j].time_start > 120)
	{
		data->animation[HAND + j].time_start = gettime();
		i++;
	}
	if ((j == HAND && i == 3) || ((j == GUN || j == SHOTGUN) && i == 5))
	{
		i = 0;
		j++;
	}
	if (j == 3)
		j = 0;
	t_img *img = get_texture(data, data->animation[HAND + j].img[i]);
	igmlx_simple_copy_to_dest(img, data->rendering_buffer, (t_uvec2){SCREEN_W - img->width + 70 , SCREEN_H - img->height});
}
