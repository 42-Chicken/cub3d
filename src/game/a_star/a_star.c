/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:26:37 by efranco           #+#    #+#             */
/*   Updated: 2025/06/06 16:41:11 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_astar.h"

t_dvec2	calculate_direction_to_target(t_dvec2 soldier, t_dvec2 target)
{
	t_dvec2	direction;

	direction.x = target.x - soldier.x;
	direction.y = target.y - soldier.y;
	return (normalize_vector(direction));
}

t_node	*init_astar_cub3d(t_list **open_list, t_cub3d_map map_info)
{
	t_node	*current_node;

	*open_list = NULL;
	current_node = create_node(NULL, map_info.soldier_pos, map_info.target_pos,
			(t_direction)-1);
	return (current_node);
}

bool	is_target_reached(t_node *node, t_dvec2 target_pos)
{
	return (fabs(node->x - target_pos.x) < 5 && fabs(node->y
			- target_pos.y) < 5);
}

t_dvec2	process_a_star_loop(t_list *open_list, t_cub3d_map map_info)
{
	t_node	*current_node;
	t_dvec2	target_direction;

	while (has_unvisited_nodes(open_list))
	{
		current_node = get_cheapest_node(open_list);
		if (!current_node)
			break ;
		current_node->viewed = true;
		if (is_target_reached(current_node, map_info.target_pos))
		{
			target_direction = calculate_direction_to_target
				(map_info.soldier_pos, map_info.target_pos);
			free_node_list(open_list);
			return (target_direction);
		}
		create_adjacent_nodes(current_node, &open_list, map_info);
	}
	return ((t_dvec2){-1.0, -1.0});
}

t_dvec2	a_star_cub3d(t_cub3d_map map_info)
{
	t_list	*open_list;
	t_node	*current_node;
	t_dvec2	error_vec;
	t_dvec2	result;

	error_vec = (t_dvec2){-1.0, -1.0};
	current_node = init_astar_cub3d(&open_list, map_info);
	if (!current_node)
		return (error_vec);
	add_to_open_list(&open_list, current_node);
	result = process_a_star_loop(open_list, map_info);
	if (result.x == -1.0 && result.y == -1.0)
		free_node_list(open_list);
	return (result);
}
