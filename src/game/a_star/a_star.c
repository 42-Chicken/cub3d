/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:26:37 by efranco           #+#    #+#             */
/*   Updated: 2025/05/28 16:24:58 by efranco          ###   ########.fr       */
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



t_dvec2	calculate_direction_to_target(t_dvec2 soldier, t_dvec2 target)
{
	t_dvec2	direction;

	direction.x = target.x - soldier.x;
	direction.y = target.y - soldier.y;

	// Normalise le vecteur pour obtenir une direction unitaire
	return (normalize_vector(direction));
}

t_dvec2	a_star_cub3d(t_cub3d_map map_info)
{
	t_list	*open_list;
	t_node	*current_node;
	t_dvec2	target_direction;
	t_dvec2	error_vec = {-1.0, -1.0};

	open_list = NULL;
	current_node = create_node(NULL, map_info.soldier_pos,
			map_info.target_pos, (t_direction)-1);
	if (!current_node)
		return (error_vec);

	add_to_open_list(&open_list, current_node);

	while (has_unvisited_nodes(open_list))
	{
		current_node = get_cheapest_node(open_list);
		if (!current_node)
			break;

		current_node->viewed = true;

		// Si on a atteint la cible
		// printf("Exploring node: (%.2f, %.2f)\n", current_node->x, current_node->y);
		// printf("Target position: (%.2f, %.2f)\n", map_info.target_pos.x, map_info.target_pos.y);
		if (fabs(current_node->x - map_info.target_pos.x) < 0.1 &&
			fabs(current_node->y - map_info.target_pos.y) < 0.1)
		{
			target_direction = calculate_direction_to_target(map_info.soldier_pos,
					map_info.target_pos);
			free_node_list(open_list);
			printf("Target reached!\n");
			return (target_direction);
		}

		create_adjacent_nodes(current_node, &open_list, map_info);
	}

	free_node_list(open_list);
	// Retourne un vecteur d'erreur si aucun chemin trouvé
	return (error_vec);
}
