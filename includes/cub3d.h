/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/28 15:45:26 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "colors.h"
# include "ft_fprintf.h"
# include "ft_strings.h"
# include "garbage.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SCREEN_W 1550
# define SCREEN_H 850

# define CUB3D_LOG_PREFIX "CUB3D"
# define CUB3D_MAX_MAP_ID_LENGTH 2

# define SPACES " \t\n\v\f\r"
# define CUB3D_MAP_SUPPORTED_CHARS "10NSEW"

typedef struct s_uvec_2
{
	unsigned int		x;
	unsigned int		y;
}						t_uvec2;

typedef struct s_dvec_2
{
	double				x;
	double				y;
}						t_dvec2;

typedef enum e_cub3d_map_values
{
	CUB3D_MAP_VOID = -1,
	CUB3D_MAP_FLOOR = '0',
	CUB3D_MAP_WALL = '1',
}						t_e_cub3d_map_values;

typedef enum e_cub3d_log_level
{
	CUB3D_LOG_DEBUG,
	CUB3D_LOG_INFO,
	CUB3D_LOG_WARNING,
	CUB3D_LOG_ERROR
}						t_e_cub3d_log_level;

typedef unsigned int	t_color;

typedef struct s_map
{
	size_t				height;
	size_t				width;
	char				**buffer;
}						t_map;

typedef struct s_player
{
	t_dvec2				position;
	double				rotation_angle;
}						t_player;

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
	t_player			player;
	t_map				map;

	t_img				*rendering_buffer;

	void				*mlx;
	void				*win;
}						t_cub3d;

// MAIN
bool					init_mlx(t_cub3d *cub3d);
void					init_mlx_hooks(t_cub3d *cub3d);
bool					destroy_mlx(t_cub3d *cub3d);
void					loop(t_cub3d *cub3d);
void					end_loop(t_cub3d *cub3d);

// PARSING
bool					parse(t_cub3d *cube3d);
bool					parsing_is_correct_file_path(t_cub3d *cub3d);
bool					parsing_check_map(t_cub3d *cub3d);
int						parsing_open_file(t_cub3d *cub3d);
bool					parse_data(t_cub3d *cub3d, int fd);
bool					parse_map(t_cub3d *cub3d, int fd);

// PLAYER
void					set_player_position_angle(t_cub3d *cub3d, t_dvec2 pos,
							double angle);

// MAP
bool					map_is_floor(t_cub3d *cub3d, size_t x, size_t y);
bool					map_is_void(t_cub3d *cub3d, size_t x, size_t y);

// LOGS
void					_info(const char *msg);
void					_debug(const char *msg);
void					_warning(const char *msg);
void					_error(const char *msg);

// UTILS
bool					is_not_only_digits(const char *str);
char					**ft_split_with_set(char const *s, char *set);
bool					endswith(char *str, char *substr);
bool					is_same_str(char *str1, char *str2);
bool					is_not_only_spaces(char *str);

#endif
