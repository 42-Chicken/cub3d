/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:06:34 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/05 09:54:17 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H

# define TEXTURES_H

# include "mlx.h"
# include "mlx_int.h"
# include <stdbool.h>

# define MAX_TEXTURES 256

typedef t_img			t_texture;
typedef struct s_cub3d	t_cub3d;

typedef enum e_textures
{
	TEXTURE_MINIMAP,
	TEXTURE_MINIMAP_BORDER,
	TEXTURE_MINIMAP_HOUSE,
	TEXTURE_MINIMAP_NORTH_INDICATION,
	TEXTURE_MINIMAP_PLAYER,
	TEXTURE_HUD_PISTOL,
	TEXTURE_HUD_HAND,
	TEXTURE_HUD_SHOTGUN,
	TEXTURE_PAUSE_MENU_RESUME,
	TEXTURE_PAUSE_MENU_RESUME_H,
	TEXTURE_PAUSE_MENU_OPTIONS,
	TEXTURE_PAUSE_MENU_OPTIONS_H,
	TEXTURE_PAUSE_MENU_QUIT,
	TEXTURE_PAUSE_MENU_QUIT_H,
	TEXTURE_PAUSE_MENU_TITLE,
	TEXTURE_OPTIONS_MENU_PLUS,
	TEXTURE_OPTIONS_MENU_PLUS_H,
	TEXTURE_OPTIONS_MENU_MINUS,
	TEXTURE_OPTIONS_MENU_MINUS_H,
	__TEXTURES_COUNT__
}						t_textures_definition;

typedef struct s_textures_atlas
{
	t_texture			*atlas[MAX_TEXTURES];
}						t_textures_atlas;

// -----------------------------------------
//
//    Getter Section
//
// -----------------------------------------

t_texture				*get_texture(t_cub3d *cub3d, int id);

// -----------------------------------------
//
//   Loader / Unloader Section
//
// -----------------------------------------

bool					load_texture(t_cub3d *cub3d, const char *path, int id);
bool					load_assets(t_cub3d *cub3d);
void					unload_assets(t_cub3d *cub3d);
void					add_asset(t_cub3d *cub3d, int id, t_img *img);

#endif
