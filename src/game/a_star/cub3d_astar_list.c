/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_astar_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:26:37 by efranco           #+#    #+#             */
/*   Updated: 2025/05/28 13:49:34 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_astar.h"

static t_list	*get_last_node(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_to_open_list(t_list **lst, t_node *node)
{
	t_list	*last;
	t_list	*new;

	new = create_list_node(node);
	if (!lst || !new)
		return;

	if (!*lst)
	{
		*lst = new;
		return;
	}

	last = get_last_node(*lst);
	last->next = new;
}

t_node	*get_cheapest_node(t_list *open_list)
{
	t_node	*cheapest_node;
	t_node	*current_node;
	double	min_cost;

	min_cost = INFINITY;
	cheapest_node = NULL;

	while (open_list)
	{
		current_node = (t_node *)open_list->content;
		if (current_node && current_node->f < min_cost && !current_node->viewed)
		{
			min_cost = current_node->f;
			cheapest_node = current_node;
		}
		open_list = open_list->next;
	}
	return (cheapest_node);
}

int	has_unvisited_nodes(t_list *open_list)
{
	t_list	*current;
	t_node	*node;

	current = open_list;
	while (current)
	{
		node = (t_node *)current->content;
		if (node && !node->viewed)
			return (1);
		current = current->next;
	}
	return (0);
}
