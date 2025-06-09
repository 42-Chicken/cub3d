/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:39:37 by efranco           #+#    #+#             */
/*   Updated: 2025/06/06 16:41:56 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_astar.h"

void	free_node_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst;
		free(lst->content);
		lst = lst->next;
		free(tmp);
	}
}
