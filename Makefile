# Main
NAME				=	cub3d
CC					=	clang

CFLAGS				=	-Wall -Werror -Wextra -O3 -march=native -pipe -flto -fomit-frame-pointer -ffast-math  -Ilibs/ft_libc/includes -Ilibs/minilibx-linux -Iincludes -fPIE -g
RM					=	rm -rf
MAKE				=	make --silent --no-print-directory -C

# Colors
RESET				=	\033[0m
BLACK				=	\033[0;30m
RED					=	\033[0;31m
GREEN				=	\033[1;32m
YELLOW				=	\033[0;33m
BLUE				=	\033[0;34m
PURPLE				=	\033[1;35m
CYAN				=	\033[1;36m
WHITE				=	\033[0;37m
GRADIENT_1			=	\033[38;2;13;71;161m
GRADIENT_2			=	\033[38;2;21;101;192m
GRADIENT_3			=	\033[38;2;33;150;243m
GRADIENT_4			=	\033[38;2;94;53;177m
GRADIENT_5			=	\033[38;2;123;31;162m
GRADIENT_6			=	\033[38;2;171;71;188m
HIGHLIGHT			=	\033[38;2;224;64;251m
BUILD_COLOR			=	\033[38;2;41;182;246m
LINK_COLOR			=	\033[38;2;149;117;205m
LOG_COLOR			=	\033[38;2;100;181;246m

# Symbols
OK					=	✓
FAIL				=	✗
INFO				=	ⓘ

# Sources and Objects
SRCS				=	src/main.c\
						src/mlx.c\
						src/loop.c\
						src/settings.c\
						src/exit_error.c\
						src/game/hud/minimap/minimap_init.c\
						src/game/hud/minimap/minimap_house.c\
						src/game/hud/minimap/minimap_render.c\
						src/game/hud/minimap/minimap_background.c\
						src/game/hud/minimap/minimap_enemies.c\
						src/game/hud/stats/stats_render.c\
						src/game/hud/stats/health_render.c\
						src/game/hud/stats/money_render.c\
						src/game/hud/stats/time_render.c\
						src/game/hud/screens/loading_screen.c\
						src/game/hud/render.c\
						src/game/game_render.c\
						src/game/hud/menus/pause_menu.c\
						src/game/hud/menus/options_menu.c\
						src/game/hud/menus/buttons.c\
						src/game/hud/menus/init_menus.c\
						src/game/controls/controls.c\
						src/game/controls/mouse.c\
						src/game/controls/controls_utils.c\
						src/game/controls/item_controls.c\
						src/images/manipulation.c\
						src/images/pixels.c\
						src/images/shapes/line.c\
						src/images/shapes/rectangle.c\
						src/images/shapes/circle.c\
						src/images/put_pixel_to_buffer.c\
						src/parsing/parsing.c\
						src/parsing/file.c\
						src/parsing/data.c\
						src/parsing/map.c\
						src/parsing/map_checks_chars.c\
						src/parsing/map_checks.c\
						src/parsing/map_entities.c\
						src/fonts/destroy_fonts.c\
						src/fonts/fonts_get.c\
						src/fonts/fonts_loader.c\
						src/fonts/fonts_print.c\
						src/game/textures/textures_loader.c\
						src/game/textures/textures.c\
						src/game/map/map_utils.c\
						src/game/player/player.c\
						src/threads/loading_thread.c\
						src/threads/r_size_t.c\
						src/utils/balloc.c\
						src/utils/vectors.c\
						src/utils/render_text.c\
						src/utils/ft_lstget.c\
						src/utils/endswith.c\
						src/utils/custom_itoa.c\
						src/utils/distance_between.c\
						src/utils/normalize_vector.c\
						src/utils/ft_clamp.c\
						src/utils/get_char_count.c\
						src/utils/is_same_str.c\
						src/utils/ft_split_with_set.c\
						src/utils/ft_is_only_digits.c\
						src/utils/is_not_only_spaces.c\
						src/game/raycaster/raycasting.c\
						src/game/raycaster/walls.c\
						src/game/raycaster/walls_textures.c\
						src/game/raycaster/floor.c\
						src/game/raycaster/sky.c\
						src/game/raycaster/utils.c\
						src/game/raycaster/vertical.c\
						src/game/raycaster/horizontal.c\
						src/game/hud/hand/hand.c\
						src/game/entities/init.c\
						src/game/entities/generate_random.c\
						src/game/entities/get_direction.c\
						src/game/entities/soldier_patern.c\
						src/game/entities/soldier_status.c\
						src/game/entities/update.c\
						src/game/entities/render.c\
						src/game/entities/door.c\
						src/game/entities/rat.c\
						src/game/entities/lamp.c\
						src/game/entities/trashcan.c\
						src/game/entities/fire_hydrant.c\
						src/game/entities/fire_baril.c\
						src/game/entities/soldier.c\
						src/game/entities/bullet.c\
						src/game/entities/money.c\
						src/game/entities/tree1.c\
						src/game/entities/tree2.c\
						src/game/entities/utils.c\
						src/game/entities/multitextures.c\
						src/game/a_star/a_star.c\
						src/game/a_star/a_star_utils.c\
						src/game/a_star/cub3d_astar_validation.c\
						src/game/a_star/cub3d_astar_list.c\
						src/game/a_star/free_node_list.c\
						src/logs/logs.c

FT_LIBC 			= ./libs/ft_libc/ft_libc.a
# IGMLX_LIB 			= ./libs/im-gui-minilibx/im-gui-minilibx.a
MLX_LIB 			= ./libs/minilibx-linux/libmlx_Linux.a
MLX_LIB_PATH 		= ./libs/minilibx-linux/

SRC_COUNT			=	$(words $(SRCS))
OBJS				=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJ_DIR				=	objects

all : $(NAME)

$(NAME) : header $(MLX_LIB) $(FT_LIBC) $(OBJ_DIR)
		@printf "$(LOG_COLOR)$(INFO) Linking $(NAME)...$(RESET)\n"
		@$(CC) -lXext -lX11 -lm -lz $(CFLAGS) $(OBJS) $(FT_LIBC) $(MLX_LIB) -o $(NAME)
		@printf "$(LINK_COLOR)$(OK) Build complete: $(NAME)$(RESET)\n"

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@
		@printf "$(BUILD_COLOR)[BUILD] %-32s -> %s$(RESET)\n" "$(notdir $<)" "$(notdir $@)"

$(OBJ_DIR): $(OBJS)
		@if [ ! -d "$(OBJ_DIR)" ]; \
			then mkdir -p "$(OBJ_DIR)"; \
		fi

$(MLX_LIB):
	@if [ ! -d "$(shell dirname $@)" ]; then \
		printf "$(LOG_COLOR)$(INFO) Fetching MinilibX sources...$(RESET)\n"; \
		git clone https://github.com/42Paris/minilibx-linux.git $(shell dirname $@) >/dev/null; \
		printf "$(LOG_COLOR)$(INFO) MinilibX repository ready.$(RESET)\n"; \
		printf "$(LOG_COLOR)$(INFO) Configuring MinilibX...$(RESET)\n"; \
		cd $(shell dirname $@) && ./configure >/dev/null && cd .. ;\
		printf "$(LINK_COLOR)$(OK) MinilibX configured$(RESET)\n"; \
	fi
	@printf "$(LOG_COLOR)$(INFO) Building MinilibX...$(RESET)\n"
	@$(MAKE) $(MLX_LIB_PATH) re
	@printf "$(LINK_COLOR)$(OK) MinilibX ready$(RESET)\n"

$(FT_LIBC) :
	@if [ ! -e "$($@)" ]; then \
		printf "$(LOG_COLOR)$(INFO) Refreshing ft_libc sources...$(RESET)\n"; \
		rm -rf $(shell dirname $@); \
		git clone git@github.com:R0-main/ft_libc.git $(shell dirname $@) >/dev/null; \
		printf "$(LOG_COLOR)$(INFO) ft_libc repository ready.$(RESET)\n"; \
	fi
	@printf "$(LOG_COLOR)$(INFO) Building ft_libc...$(RESET)\n"
	@$(MAKE) $(shell dirname $@) SAFE=1
	@printf "$(LINK_COLOR)$(OK) ft_libc ready$(RESET)\n"

dev	 : clean-objs all
	valgrind --track-fds=yes --trace-children=yes --show-leak-kinds=all --leak-check=full -q ./cub3d maps/valids/map.cub

header:
		@printf "$(GRADIENT_1)  _____         _      _____ ______$(RESET)\n"
		@printf "$(GRADIENT_2) /  __ \\       | |    |____ ||  _  \\ $(RESET)\n"
		@printf "$(GRADIENT_3) | /  \\/ _   _ | |__      / /| | | |$(RESET)\n"
		@printf "$(GRADIENT_4) | |    | | | || '_ \\     \\ \\| | | |$(RESET)\n"
		@printf "$(GRADIENT_5) | \\__/\\| |_| || |_) |.___/ /| |/ /$(RESET)\n"
		@printf "$(GRADIENT_6) \\____/ \\__,_||_.___/ \\____/ |___/$(RESET)\n"
		@printf "\n"
		@printf "$(HIGHLIGHT)Launching gradient build for $(NAME)...$(RESET)\n"

clean-objs :
		@printf "$(LOG_COLOR)$(INFO) Removing object files...$(RESET)\n"
		@$(RM) $(OBJ_DIR)
		@printf "$(LINK_COLOR)$(OK) Objects cleaned$(RESET)\n"

clean : clean-objs
		@printf "$(LOG_COLOR)$(INFO) Cleaning ft_libc artifacts...$(RESET)\n"
		@$(MAKE) $(shell dirname $(FT_LIBC)) fclean
		@printf "$(LOG_COLOR)$(INFO) Cleaning MinilibX artifacts...$(RESET)\n"
		@$(MAKE) $(shell dirname $(MLX_LIB)) clean
		@printf "$(LINK_COLOR)$(OK) External libraries cleaned$(RESET)\n"

fclean : clean
		@printf "$(LOG_COLOR)$(INFO) Removing binary $(NAME)...$(RESET)\n"
		@$(RM) $(NAME)
		@printf "$(LINK_COLOR)$(OK) Binary removed$(RESET)\n"

re : fclean all

.PHONY: all clean fclean re header
