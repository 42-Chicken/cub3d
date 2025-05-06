/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:06:34 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 09:18:50 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONTS_H

# define FONTS_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include "vectors.h"
# include <limits.h>
# include <stdbool.h>

typedef struct s_cub3d	t_cub3d;
typedef unsigned int	t_color;

typedef struct s_igmlx_font
{
	t_img				*letters[CHAR_MAX];
	char				*path;
	char				*name;
	t_color				color;
	unsigned int		size_mutliplier;
	t_uvec2				length;
	t_uvec2				inner_offset;
}						t_igmlx_font;

typedef struct s_igmlx_font_params
{
	t_color				color;
	unsigned int		size_multiplier;
	t_uvec2				inner_offset;
}						t_igmlx_font_params;

// -----------------------------------------
//
//    Getter Section
//
// -----------------------------------------

t_igmlx_font			*get_font(t_cub3d *igmlx, char *path);

// -----------------------------------------
//
//   Loader / Unloader Section
//
// -----------------------------------------
void					igmlx_destroy_fonts_list(t_cub3d *igmlx,
							t_list **fonts);
void					igmlx_load_font(t_cub3d *igmlx, char *path, char *name,
							t_igmlx_font_params params);
void					igmlx_put_str_to_buffer(t_igmlx_font *font, char *str, t_img *buffer, t_uvec2 pos);

#endif
