/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/24 11:10:53 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "colors.h"
# include "ft_fprintf.h"
# include "ft_strings.h"
# include "garbage.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define CUB3D_LOG_PREFIX "CUB3D"
# define CUB3D_MAX_MAP_ID_LENGTH 2

# define SPACES " \t\n\v\f\r"

typedef enum e_cub3d_log_level
{
	CUB3D_LOG_DEBUG,
	CUB3D_LOG_INFO,
	CUB3D_LOG_WARNING,
	CUB3D_LOG_ERROR
}						t_e_cub3d_log_level;

typedef unsigned int	t_color;

typedef struct s_cub3d
{
	const char			**av;
	int					ac;

	char				*north_texture_path;
	char				*south_texture_path;
	char				*west_texture_path;
	char				*east_texture_path;

	t_color				floor_color;
	t_color				ceiling_color;
}						t_cub3d;

// PARSING
bool					parse(t_cub3d *cube3d);
bool					parsing_is_correct_file_path(t_cub3d *cub3d);
int						parsing_open_file(t_cub3d *cub3d);
bool					parse_data(t_cub3d *cub3d, int fd);

// LOGS
void					_info(const char *msg);
void					_debug(const char *msg);
void					_warning(const char *msg);
void					_error(const char *msg);

// UTILS
bool					is_not_only_digits(const char *str);
char					**ft_split_with_set(char const *s, char *set);
bool					endswith(char *str, char *substr);

#endif
