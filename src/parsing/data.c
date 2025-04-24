/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:50:29 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/24 12:58:27 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parsing_get_identifier(char **line, char **buffer)
{
	int	i;
	int	k;

	i = 0;
	while ((*line)[i] && ft_isspace((*line)[i]))
		i++;
	k = 0;
	while ((*line)[i + k] && !ft_isspace((*line)[i + k]))
		k++;
	*buffer = ft_substr((*line), i, k);
	return (k + i);
}

static bool	parsing_set_and_read_id_value(char **target, char *value)
{
	*target = ft_strtrim(value, SPACES);
	send_pointer_to_main_context(*target);
	return (true);
}

static bool	parsing_set_and_read_color_id_value(t_color *target, char *value)
{
	char	**splitted;
	int		i;
	int		d;

	i = 0;
	splitted = ft_split_with_set(value, SPACES ",");
	if (!splitted)
		return (false);
	i = 0;
	d = 0;
	while (splitted[i] && i < 3)
	{
		if (is_not_only_digits(splitted[i]) == false
			|| ft_atoi(splitted[i]) > 255 || ft_strlen(splitted[i]) > 3)
			return (false);
		*target = ((*target << d) | ft_atoi(splitted[i]));
		i++;
		d += 8;
	}
	return (true);
}

static bool	parsing_map_identifier(t_cub3d *cub3d, char *buffer, char *value)
{
	if (ft_strncmp("NO", buffer, ft_strlen(buffer)) == 0)
		return (parsing_set_and_read_id_value(&cub3d->north_texture_path,
				value));
	if (ft_strncmp("SO", buffer, ft_strlen(buffer)) == 0)
		return (parsing_set_and_read_id_value(&cub3d->south_texture_path,
				value));
	if (ft_strncmp("WE", buffer, ft_strlen(buffer)) == 0)
		return (parsing_set_and_read_id_value(&cub3d->west_texture_path,
				value));
	if (ft_strncmp("EA", buffer, ft_strlen(buffer)) == 0)
		return (parsing_set_and_read_id_value(&cub3d->east_texture_path,
				value));
	if (ft_strncmp("F", buffer, ft_strlen(buffer)) == 0)
		return (parsing_set_and_read_color_id_value(&cub3d->floor_color,
				value));
	if (ft_strncmp("C", buffer, ft_strlen(buffer)) == 0)
		return (parsing_set_and_read_color_id_value(&cub3d->ceiling_color,
				value));
	return (true);
}

bool	parse_data(t_cub3d *cub3d, int fd)
{
	char	*line;
	char	*id;
	int		offset;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		offset = parsing_get_identifier(&line, &id);
		if (ft_strlen(id) <= 0)
			continue ;
		if (parsing_map_identifier(cub3d, id, line + offset) == false)
			return (false);
	}
	return (true);
}
