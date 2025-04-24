/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:26:56 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/24 14:55:26 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	size_t	i;

	i = 0;
	c = head;
	while (c)
	{
		cub3d->map.buffer[i++] = (char *)c->content;
		send_pointer_to_main_context(c->content);
		c = c->next;
	}
}

bool	parse_map(t_cub3d *cub3d, int fd)
{
	t_list	*head;

	head = parsing_get_map_lines(fd);
	if (!head)
		return (_error("no map lines found!"), false);
	cub3d->map.width = parsing_get_longest_line(head);
	cub3d->map.height = ft_lstsize(head);
	cub3d->map.buffer = safe_malloc(sizeof(char *) * cub3d->map.height);
	parsing_fill_map_buffer(cub3d, head);
	if (parsing_check_map(cub3d) == false)
		return (false);
	return (true);
}
