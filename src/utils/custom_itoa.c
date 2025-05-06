/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 08:44:50 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 08:41:05 by rguigneb         ###   ########.fr       */
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

void	custom_itoa(int n, char *buffer)
{
	size_t	i;
	size_t	is_negative;
	size_t	number_len;
	long	nb;

	nb = (long)n;
	i = get_number_len(nb);
	number_len = i;
	is_negative = nb < 0;
	if (is_negative)
		nb = -nb;
	while (--i < number_len)
	{
		buffer[i] = nb % 10 + '0';
		nb /= 10;
	}
	if (is_negative)
		buffer[0] = '-';
	buffer[number_len] = 0;
}
