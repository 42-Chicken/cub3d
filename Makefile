# Main
NAME				=	cub3d
CC					=	clang

CFLAGS				=	-Wall -Werror -Wextra -O3 -O2 -ffast-math -march=native -Ilibs/ft_libc/includes -Ilibs/minilibx-linux -Iincludes -fPIE -g
RM					=	rm -rf
MAKE				=	make --no-print-directory -C

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

# Symbols
OK					=	✓
FAIL				=	✗
INFO				=	ⓘ

# Sources and Objects
SRCS				=	src/main.c\
						src/mlx.c\
						src/loop.c\
						src/exit_error.c\
						src/minimap/minimap_init.c\
						src/minimap/minimap_house.c\
						src/minimap/minimap_render.c\
						src/minimap/minimap_background.c\
						src/controls/controls.c\
						src/images/manipulation.c\
						src/images/shapes/line.c\
						src/images/shapes/rectangle.c\
						src/images/shapes/circle.c\
						src/images/put_pixel_to_buffer.c\
						src/parsing/parsing.c\
						src/parsing/file.c\
						src/parsing/data.c\
						src/parsing/map.c\
						src/textures/textures_loader.c\
						src/textures/textures.c\
						src/parsing/map_checks.c\
						src/map/map_utils.c\
						src/player/player.c\
						src/utils/endswith.c\
						src/utils/distance_between.c\
						src/utils/normalize_vector.c\
						src/utils/ft_clamp.c\
						src/utils/get_char_count.c\
						src/utils/is_same_str.c\
						src/utils/ft_split_with_set.c\
						src/utils/ft_is_only_digits.c\
						src/utils/is_not_only_spaces.c\
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
		@$(CC) -lXext -lX11 -lm -lz $(CFLAGS) $(OBJS) $(FT_LIBC) $(MLX_LIB) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@
		@printf "$(GREEN)$(OK)$(RESET)"

$(OBJ_DIR): $(OBJS)
		@if [ ! -d "$(OBJ_DIR)" ]; \
			then mkdir -p "$(OBJ_DIR)"; \
		fi
		@if [ ! -e "$(NAME)" ]; then \
			printf "]" ; \
			printf "\n" ; \
		fi

$(MLX_LIB):
	@if [ ! -e "$($@)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(shell dirname $@); \
		cd $(shell dirname $@) && ./configure && cd .. ;\
	fi;
	make re -C $(MLX_LIB_PATH) --no-print-directory

$(FT_LIBC) :
	@if [ ! -e "$(shell dirname $@)" ]; then \
		git clone git@github.com:R0-main/ft_libc.git $(shell dirname $@); \
	fi;
	@$(MAKE) $(shell dirname $@) SAFE=1

dev	 : clean-objs all
	valgrind --track-fds=yes --trace-children=yes --show-leak-kinds=all --leak-check=full -q ./cub3d maps/valids/map.cub

header:
		@printf "\
		 _____         _      _____ ______\n\
		/  __ \       | |    |____ ||  _  \\n\
		| /  \/ _   _ | |__      / /| | | |\n\
		| |    | | | || '_ \     \ \| | | |\n\
		| \__/\| |_| || |_) |.___/ /| |/ /\n\
		\____/ \__,_||_.__/ \____/ |___/\n\
		" ;
		@printf  "\n";
		@if [ ! -e "$(NAME)" ]; \
			then printf "Compiling Project : ["; \
		fi

clean-objs :
		@$(RM) $(OBJ_DIR)

clean : clean-objs
		@$(MAKE) $(shell dirname $(FT_LIBC)) fclean
		@$(MAKE) $(shell dirname $(MLX_LIB)) clean
		@$(MAKE) $(shell dirname $(IGMLX_LIB)) fclean

fclean : clean
		@$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re header
