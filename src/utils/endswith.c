/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endswith.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:55:16 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/24 09:44:02 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	endswith(char *str, char *substr)
{
	int	i;
	int	k;
	int	sub_len;
	int	str_len;

	if (!str)
		return (false);
	if (!substr)
		return (false);
	sub_len = ft_strlen(substr);
	str_len = ft_strlen(str);
	i = str_len - 1;
	while (str[i] && str_len - i <= sub_len)
	{
		k = 0;
		while (str[i + k] && str[i + k] == substr[k])
			k++;
		if (substr[k] == 0)
			return (true);
		i--;
	}
	return (false);
}
