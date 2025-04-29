/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:06:34 by rguigneb          #+#    #+#             */
/*   Updated: 2025/04/29 12:37:05 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H

# define TEXTURES_H

# include "mlx.h"
# include "mlx_int.h"
# include <stdbool.h>

# define MAX_TEXTURES 256

typedef t_img		t_texture;

typedef enum e_textures
{
	MAP,
	TEXTURE_MINIMAP_BORDER,
	TEXTURE_MINIMAP_NORTH_INDICATION,
	TEXTURE_MINIMAP_PLAYER,
}					t_textures_definition;

typedef struct s_textures_atlas
{
	t_texture		*atlas[MAX_TEXTURES];
}					t_textures_atlas;

// -----------------------------------------
//
//    Getter Section
//
// -----------------------------------------

t_texture			*get_texture(int id);
t_textures_atlas	*get_textures_atlas(void);

// -----------------------------------------
//
//   Loader / Unloader Section
//
// -----------------------------------------

bool				load_texture(void *mlx, const char *path, int id);
bool				load_assets(void *mlx);
void				unload_assets(void *mlx);
void				add_asset(int id, t_img *img);

#endif
