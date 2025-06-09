/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_astar.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:26:37 by efranco           #+#    #+#             */
/*   Updated: 2025/06/06 16:41:20 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ASTAR_H
# define CUB3D_ASTAR_H

# include <cub3d.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_directions
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
}					t_direction;

typedef struct s_node
{
	double			x;
	double			y;
	bool			viewed;
	double			f;
	double			g;
	double			h;
	t_dvec2			up;
	t_dvec2			down;
	t_dvec2			right;
	t_dvec2			left;
	t_direction		prev_direction;
	struct s_node	*prev;
}					t_node;

typedef struct s_cub3d_map
{
	char			**map;
	int				width;
	int				height;
	t_dvec2			soldier_pos;
	t_dvec2			target_pos;
}					t_cub3d_map;

// Fonctions principales
t_dvec2				a_star_cub3d(t_cub3d_map map_info);
t_dvec2				calculate_direction_to_target(t_dvec2 soldier,
						t_dvec2 target);
t_dvec2				normalize_vector(t_dvec2 vec);

// Fonctions utilitaires
void				free_node_list(t_list *lst);
double				distance_between(t_dvec2 pos1, t_dvec2 pos2);
void				init_adjacent_positions(t_node *node);
t_node				*create_node(t_node *parent, t_dvec2 coord_start,
						t_dvec2 coord_goal, t_direction prev_direction);
t_list				*create_list_node(t_node *current);
void				add_to_open_list(t_list **lst, t_node *node);
int					is_valid_position(t_dvec2 coord, t_cub3d_map map_info);
int					is_walkable(char **map, t_dvec2 coord);
int					check_coord_in_list(t_list *open_list, t_dvec2 coord);
void				create_adjacent_nodes(t_node *node, t_list **open_list,
						t_cub3d_map map_info);
t_node				*get_cheapest_node(t_list *open_list);
int					has_unvisited_nodes(t_list *open_list);

#endif
