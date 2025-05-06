/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:06:34 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/06 14:29:09 by rguigneb         ###   ########.fr       */
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

# define TEXTURES_PATHS "\
assets/loading_screens/1.xpm\n\
assets/minimap/minimap_border.xpm\n\
assets/minimap/minimap_house.xpm\n\
assets/minimap/minimap_north_indication.xpm\n\
assets/minimap/minimap_player.xpm\n\
assets/pistol.xpm\n\
assets/fist.xpm\n\
assets/shotgun.xpm\n\
assets/menus/pause/resume.xpm\n\
assets/menus/pause/resume_hover.xpm\n\
assets/menus/pause/options.xpm\n\
assets/menus/pause/options_hover.xpm\n\
assets/menus/pause/quit.xpm\n\
assets/menus/pause/quit_hover.xpm\n\
assets/menus/pause/title.xpm\n\
assets/menus/options/title.xpm\n\
assets/menus/options/plus.xpm\n\
assets/menus/options/plus_hover.xpm\n\
assets/menus/options/minus.xpm\n\
assets/menus/options/minus_hover.xpm\n\
assets/menus/back.xpm\n\
assets/menus/back_hover.xpm\n\
"

typedef enum e_textures
{
	TEXTURE_LOADING_SCREEN,
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
	TEXTURE_OPTIONS_MENU_TITLE,
	TEXTURE_OPTIONS_MENU_PLUS,
	TEXTURE_OPTIONS_MENU_PLUS_H,
	TEXTURE_OPTIONS_MENU_MINUS,
	TEXTURE_OPTIONS_MENU_MINUS_H,
	TEXTURE_OPTIONS_MENU_BACK,
	TEXTURE_OPTIONS_MENU_BACK_H,
	__TEXTURES_COUNT__,
	__TEXTURE_MINIMAP__,
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
