/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:06:34 by rguigneb          #+#    #+#             */
/*   Updated: 2025/05/23 15:12:28 by rguigneb         ###   ########.fr       */
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

// assets/loading_screens/1.xpm\n
# define TEXTURES_PATHS "\
assets/42.xpm\n\
assets/loading_screens/1.xpm\n\
assets/minimap/minimap_border.xpm\n\
assets/minimap/minimap_house.xpm\n\
assets/minimap/bowser.xpm\n\
assets/minimap/minimap_door.xpm\n\
assets/minimap/minimap_money.xpm\n\
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
assets/img/pistol1.xpm\n\
assets/img/pistol2.xpm\n\
assets/img/pistol3.xpm\n\
assets/img/pistol4.xpm\n\
assets/img/pistol5.xpm\n\
assets/img/punch1.xpm\n\
assets/img/punch2.xpm\n\
assets/img/punch3.xpm\n\
assets/img/shotgun1.xpm\n\
assets/img/shotgun2.xpm\n\
assets/img/shotgun3.xpm\n\
assets/img/shotgun4.xpm\n\
assets/img/shotgun5.xpm\n\
assets/walls/wall.xpm\n\
assets/entities/soldier/front.xpm\n\
assets/entities/soldier/front_right.xpm\n\
assets/entities/soldier/right.xpm\n\
assets/entities/soldier/back_right.xpm\n\
assets/entities/soldier/back.xpm\n\
assets/entities/soldier/back_left.xpm\n\
assets/entities/soldier/left.xpm\n\
assets/entities/soldier/front_left.xpm\n\
assets/entities/money.xpm\n\
assets/road.xpm\n\
F assets/walls/wall3.xpm\n\
D assets/walls/door.xpm\n\
B assets/walls/building.xpm\n\
G assets/walls/wall2.xpm\n\
H assets/walls/wall3.xpm\n\
"

typedef enum e_textures
{
	TEXTURE_42,
	TEXTURE_LOADING_SCREEN,
	TEXTURE_MINIMAP_BORDER,
	TEXTURE_MINIMAP_HOUSE,
	TEXTURE_MINIMAP_ENEMY,
	TEXTURE_MINIMAP_DOOR,
	TEXTURE_MINIMAP_MONEY,
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
	TEXTURE_PISTOL1,
	TEXTURE_PISTOL2,
	TEXTURE_PISTOL3,
	TEXTURE_PISTOL4,
	TEXTURE_PISTOL5,
	TEXTURE_PUNCH1,
	TEXTURE_PUNCH2,
	TEXTURE_PUNCH3,
	TEXTURE_SHOTGUN1,
	TEXTURE_SHOTGUN2,
	TEXTURE_SHOTGUN3,
	TEXTURE_SHOTGUN4,
	TEXTURE_SHOTGUN5,
	TEXTURE_WALL_DEFAULT,
	TEXTURE_ENTITY_SOLDIER_FRONT,
	TEXTURE_ENTITY_SOLDIER_FRONT_RIGHT,
	TEXTURE_ENTITY_SOLDIER_RIGHT,
	TEXTURE_ENTITY_SOLDIER_BACK_RIGHT,
	TEXTURE_ENTITY_SOLDIER_BACK,
	TEXTURE_ENTITY_SOLDIER_BACK_LEFT,
	TEXTURE_ENTITY_SOLDIER_LEFT,
	TEXTURE_ENTITY_SOLDIER_FRONT_LEFT,
	TEXTURE_ENTITY_MONEY,
	TEXTURE_FLOOR,
	TEXTURE_WALL_NORTH,
	TEXTURE_WALL_SOUTH,
	TEXTURE_WALL_EAST,
	TEXTURE_WALL_WEST,
	__TEXTURES_COUNT__,
	__TEXTURE_MINIMAP__,
}						t_textures_definition;

typedef struct s_texture_link
{
	char				link;
	t_texture			*texture;
}						t_texture_link;

typedef struct s_textures_atlas
{
	t_texture			*atlas[MAX_TEXTURES];
	size_t				links_count;
	t_texture_link		links[MAX_TEXTURES];
}						t_textures_atlas;

// -----------------------------------------
//
//    Getter Section
//
// -----------------------------------------

t_texture				*get_texture(t_cub3d *cub3d, int id);
t_texture				*get_linked_texture(t_cub3d *cub3d, char link);

// -----------------------------------------
//
//   Loader / Unloader Section
//
// -----------------------------------------

bool					load_texture(t_cub3d *cub3d, const char *path, int id);
bool					load_assets(t_cub3d *cub3d);
void					unload_assets(t_cub3d *cub3d);
void					add_asset(t_cub3d *cub3d, int id, t_img *img);
void					add_asset_link(t_cub3d *cub3d, char link, t_img *img);

#endif
