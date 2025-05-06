/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_size_t.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:51:28 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 09:14:59 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	r_size_t(pthread_mutex_t *mutex, size_t *value)
{
	size_t	r;

	pthread_mutex_lock(mutex);
	r = *value;
	pthread_mutex_unlock(mutex);
	return (r);
}
