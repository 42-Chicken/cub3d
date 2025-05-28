/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_astar_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:26:37 by efranco           #+#    #+#             */
/*   Updated: 2025/05/28 13:33:40 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_astar.h"

int	is_valid_position(t_dvec2 coord, t_cub3d_map map_info)
{
	if (coord.x < 0 || coord.y < 0 ||
		coord.x >= map_info.width || coord.y >= map_info.height)
		return (0);
	return (1);
}

int	is_walkable(char **map, t_dvec2 coord)
{
	int	x = (int)coord.x;
	int	y = (int)coord.y;

	// Adaptation selon votre système de map cub3d
	// '1' = mur, '0' = espace libre
	if (map[y][x] == '1')
		return (0);
	return (1);
}


int	check_coord_in_list(t_list *open_list, t_dvec2 coord)
{
	t_list	*current;
	t_node	*node;

	current = open_list;
	while (current)
	{
		node = (t_node *)current->content;
		if (node && fabs(node->x - coord.x) < 0.1 &&
			fabs(node->y - coord.y) < 0.1)
			return (0);  // Coordonnée déjà dans la liste
		current = current->next;
	}
	return (1);  // Coordonnée pas dans la liste
}



void	create_adjacent_nodes(t_node *node, t_list **open_list,
		t_cub3d_map map_info)
{
	t_dvec2	directions[4];
	int		i;
	t_node	*new_node;

	directions[0] = node->up;
	directions[1] = node->down;
	directions[2] = node->left;
	directions[3] = node->right;

	i = 0;
	while (i < 4)
	{
		if (is_valid_position(directions[i], map_info) &&
			is_walkable(map_info.map, directions[i]) == 1 &&
			check_coord_in_list(*open_list, directions[i]))
		{
			new_node = create_node(node, directions[i],
					map_info.target_pos, (t_direction)i);
			if (new_node)
				add_to_open_list(open_list, new_node);
		}
		i++;
	}
}
