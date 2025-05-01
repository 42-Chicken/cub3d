/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   money_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:51:26 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 15:52:48 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	get_number_len(long n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		++i;
	}
	while (n > 0 && ++i)
		n /= 10;
	return (i);
}

static char *custom_itoa(int n)
{
	size_t	i;
	size_t	is_negative;
	size_t	number_len;
	long	nb;
	char	*result;

	nb = (long)n;
	i = get_number_len(nb);
	is_negative = nb < 0;
	number_len = i;
	result = (char *)safe_malloc(number_len * sizeof(char) + 2);
	result[0] = '$';
	if (!result)
		return (NULL);
	if (is_negative)
		nb = -nb;
	while (--i < number_len)
	{
		result[i + 1] = nb % 10 + '0';
		nb /= 10;
	}
	if (is_negative)
		result[0] = '-';
	result[number_len + 1] = 0;
	return (result);
}

void render_stats_money(t_cub3d *cub3d)
{
	char	*money;

	money = custom_itoa(cub3d->player.money);
	render_text(cub3d, GTA_FONT_BLUE_NAME, money, (t_uvec2){SCREEN_W - 275 - ft_strlen(money) * 19, 50});
	safe_free(money);
}
