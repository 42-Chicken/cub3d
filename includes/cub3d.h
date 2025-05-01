/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/01 09:34:15 by rguigneb         ###   ########.fr       */
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
# include "textures.h"
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

# define MINIMAP_OFFSET 25
# define MINIMAP_TILE_SIZE 25

typedef struct s_vec_2
{
	int					x;
	int					y;
}						t_vec2;

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

typedef struct s_fvec2
{
	float				x;
	float				y;
}						t_fvec2;

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
	double				rotation_angle_add;
	t_dvec2				direction;
	double				cos_r;
	double				sin_r;
}						t_player;

typedef struct s_minimap
{
	t_uvec2				border_pos;
	t_uvec2				north_pos;
	t_uvec2				player_pos;
}						t_minimap;

typedef struct s_settings
{
	bool				debug;
	double				fNear;
	double				fFar;
	unsigned char		fov;
}						t_settings;

typedef struct s_cub3d
{
	const char			**av;
	int					ac;

	bool				error;

	char				*north_texture_path;
	char				*south_texture_path;
	char				*west_texture_path;
	char				*east_texture_path;

	t_color				floor_color;
	t_color				ceiling_color;
	t_player			player;
	t_map				map;

	t_settings			settings;

	t_img				*rendering_buffer;

	t_minimap			minimap;
	t_textures_atlas	textures_atlas;

	void				*mlx;
	void				*win;
}						t_cub3d;

// MAIN
bool					init_mlx(t_cub3d *cub3d);
void					init_mlx_hooks(t_cub3d *cub3d);
bool					destroy_mlx(t_cub3d *cub3d);
void					loop(t_cub3d *cub3d);
void					end_loop(t_cub3d *cub3d);
void					exit_error(const char *msg);

// PARSING
bool					parse(t_cub3d *cube3d);
bool					parsing_is_correct_file_path(t_cub3d *cub3d);
bool					parsing_check_map(t_cub3d *cub3d);
int						parsing_open_file(t_cub3d *cub3d);
bool					parse_data(t_cub3d *cub3d, int fd);
bool					parse_map(t_cub3d *cub3d, int fd);

// MINIMAP
void					render_minimap(t_cub3d *cub3d);
bool					init_minimap(t_cub3d *cub3d);

// CONTROLS
void					on_key_pressed(int key, t_cub3d *cub3d);
void					on_key_released(int key, t_cub3d *cub3d);

// IMAGES
void					put_pixel_to_buffer(t_img *buffer, t_uvec2 pos,
							t_color color);
void					put_pixel_to_buffer_inside_shape(t_img *buffer,
							t_uvec2 pos, t_color color);
void					draw_line(t_img *buffer, int color, t_vec2 start,
							t_vec2 end);
void					draw_rect(t_img *buffer, int color, t_uvec2 start,
							t_uvec2 end);

t_color					*get_pixel(t_img *img, t_uvec2 pos);
t_color					get_pixel_color(t_img *img, t_uvec2 pos);
t_color					igmlx_melt_colors(t_color input, t_color filter);
void					igmlx_apply_color_filter(t_img *img, t_color filter);
void					igmlx_copy_to_dest_ignore_null(t_img *origin,
							t_uvec2 origin_pos, t_uvec2 length, t_img *dest,
							t_uvec2 dest_pos);
void					igmlx_copy_to_dest(t_img *origin, t_uvec2 origin_pos,
							t_uvec2 length, t_img *dest, t_uvec2 dest_pos);
void					igmlx_set_to_null(t_img *origin, t_uvec2 origin_pos,
							t_uvec2 length);
void					igmlx_simple_copy_to_dest_ignore_null(t_img *origin,
							t_img *dest, t_uvec2 dest_pos);
// PLAYER
void					set_player_position_angle(t_cub3d *cub3d, t_dvec2 pos,
							double angle);
void					handle_player_movement(t_cub3d *cub3d);

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
