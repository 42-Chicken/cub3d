/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:26:56 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/22 10:16:04 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static t_list	*parsing_get_map_lines(int fd)
{
	char	*line;
	t_list	*head;
	t_list	*tmp;

	head = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strlen(line) <= 0 || is_not_only_spaces(line) == false)
			continue ;
		tmp = ft_lstnew(line);
		ft_lstadd_back(&head, tmp);
	}
	return (head);
}

static size_t	parsing_get_longest_line(t_list *head)
{
	t_list	*c;
	size_t	max;
	size_t	len;

	c = head;
	max = 0;
	while (c)
	{
		len = (size_t)ft_strlen((char *)c->content);
		if (len > max)
			max = len;
		c = c->next;
	}
	return (max);
}

static void	parsing_fill_map_buffer(t_cub3d *cub3d, t_list *head)
{
	t_list	*c;
	size_t	y;
	size_t	x;

	y = 0;
	c = head;
	while (c)
	{
		cub3d->map.buffer[y++] = (char *)c->content;
		send_pointer_to_main_context(c->content);
		c = c->next;
	}
	y = 0;
	while (y < cub3d->map.height)
	{
		x = 0;
		while (x < ft_strlen(cub3d->map.buffer[y]))
		{
			if (ft_isspace(cub3d->map.buffer[y][x]) == true)
				cub3d->map.buffer[y][x] = CUB3D_MAP_VOID;
			x++;
		}
		y++;
	}
}

void	parsing_set_player_data(t_cub3d *cub3d)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < cub3d->map.height)
	{
		x = 0;
		while (x < ft_strlen(cub3d->map.buffer[y]))
		{
			if (cub3d->map.buffer[y][x] == 'N')
				set_player_position_angle(cub3d, (t_dvec2){(double)x + 0.5,
					(double)y + 0.5}, M_PI + M_PI / 2);
			if (cub3d->map.buffer[y][x] == 'S')
				set_player_position_angle(cub3d, (t_dvec2){(double)x + 0.5,
					(double)y + 0.5}, M_PI / 2);
			if (cub3d->map.buffer[y][x] == 'E')
				set_player_position_angle(cub3d, (t_dvec2){(double)x + 0.5,
					(double)y + 0.5}, M_PI * 2);
			if (cub3d->map.buffer[y][x] == 'W')
				set_player_position_angle(cub3d, (t_dvec2){(double)x + 0.5,
					(double)y + 0.5}, M_PI);
			x++;
		}
		y++;
	}
}

bool	parse_map(t_cub3d *cub3d, int fd)
{
	t_list	*head;
	t_uvec2	p_pos;

	head = parsing_get_map_lines(fd);
	if (!head)
		return (_error("no map lines found!"), false);
	cub3d->map.width = parsing_get_longest_line(head);
	cub3d->map.height = ft_lstsize(head);
	cub3d->map.buffer = safe_malloc(sizeof(char *) * cub3d->map.height);
	send_pointer_to_main_context(cub3d->map.buffer);
	parsing_fill_map_buffer(cub3d, head);
	cub3d->player.location = (t_dvec2){-1, -1};
	parsing_set_player_data(cub3d);
	p_pos = (t_uvec2){cub3d->player.location.x, cub3d->player.location.y};
	if (cub3d->player.location.x == -1 || cub3d->player.location.y == -1)
		return (_error("no player spawn position in the map!"), false);
	parse_map_entities(cub3d);
	cub3d->spawn_point = p_pos;
	cub3d->map.buffer[p_pos.y][p_pos.x] = CUB3D_MAP_FLOOR;
	if (parsing_check_map(cub3d) == false)
		return (false);
	return (true);
}
