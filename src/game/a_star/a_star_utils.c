/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_astar_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:26:37 by efranco           #+#    #+#             */
/*   Updated: 2025/05/28 13:33:40 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_astar.h"



void	init_adjacent_positions(t_node *node)
{
	node->up.x = node->x;
	node->up.y = node->y - 1.0;
	node->down.x = node->x;
	node->down.y = node->y + 1.0;
	node->left.x = node->x - 1.0;
	node->left.y = node->y;
	node->right.x = node->x + 1.0;
	node->right.y = node->y;
}

t_node	*create_node(t_node *parent, t_dvec2 coord_start, t_dvec2 coord_goal,
		t_direction prev_direction)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);

	node->x = coord_start.x;
	node->y = coord_start.y;
	node->viewed = false;

	// Calcul des coûts G, H et F
	if (parent)
		node->g = parent->g + 1.0;  // Coût depuis le début
	else
		node->g = 0.0;

	node->h = distance_between(coord_start, coord_goal);  // Heuristique
	node->f = node->g + node->h;  // Coût total

	node->prev = parent;
	node->prev_direction = prev_direction;
	init_adjacent_positions(node);

	return (node);
}

t_list	*create_list_node(t_node *current)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->content = current;
	lst->next = NULL;
	return (lst);
}
