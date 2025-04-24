/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_same_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:03:05 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/24 14:03:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_same_str(char *str1, char *str2)
{
	return (str1 && str2 && ft_strlen(str1) == ft_strlen(str2)
		&& ft_strncmp(str1, str2, ft_strlen(str1)) == 0);
}
