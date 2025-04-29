/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:31:42 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/29 12:32:22 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(const char *msg)
{
	_error(msg);
	free_all_contexts_garbage();
	exit(EXIT_FAILURE);
}
