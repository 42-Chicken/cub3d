/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:53:02 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 15:04:04 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void *balloc(size_t size)
{
	void *ptr;

	ptr = safe_malloc(size);
	if (!ptr)
	{
		_error("a malloc failed!");
		return (NULL);
	}
	ft_bzero(ptr, size);
	return (ptr);
}

void *balloc_(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		_error("a malloc failed!");
		return (NULL);
	}
	ft_bzero(ptr, size);
	return (ptr);
}
