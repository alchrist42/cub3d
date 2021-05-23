NAME		=	cub3D
NAME_B		=	lab3D

SRCS_FILES	= 	main.c \
				parcer.c \
				parcer_map.c \
				parcer_lines.c \
				parcer_utils.c \
				raise_error.c \
				window.c \
				game.c \
				hooks.c \
				rays.c \
				rays_checks.c \
				get_img.c \
				get_img_helpers.c \
				inicialise_structs.c \
				mooving.c \
				save.c \
				utils.c \
				gnl/get_next_line.c \

SRCS_B_FILES	=	main_bonus.c \
					parcer_bonus.c \
					parcer_map_bonus.c \
					parcer_lines_bonus.c \
					parcer_utils_bonus.c \
					raise_error_bonus.c \
					window_bonus.c \
					game_bonus.c \
					hooks_bonus.c \
					rays_bonus.c \
					rays_checks_bonus.c \
					get_img_bonus.c \
					get_img_helpers_bonus.c \
					inicialise_structs_bonus.c \
					move_bonus.c \
					rotate_bonus.c \
					save_bonus.c \
					utils_bonus.c \
					minimap_bonus.c \
					hud_bonus.c \
					gnl/get_next_line.c \

SRCS_FOLDER	=	src/
SRCS_B_FLD	=	src_bonus/
HEADER		=	include/cub3d.h

SRCS		= 	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))
SRCS_B		=	$(addprefix $(SRCS_B_FLD),$(SRCS_B_FILES))
OBJS		=	$(patsubst %.c,%.o,$(SRCS))
OBJS_B		=	$(patsubst %.c,%.o,$(SRCS_B))

INCLUDE		=	-I./include -I./src/libft/ -I./src/gnl/ -I./src/mlx/

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -MMD
FRAMEWORK	=	-framework OpenGL -framework AppKit
RM			=	rm -f

LIBC		=	ar rcs

MLX = ./src/mlx/libmlx.a
LIB = ./src/libft/libft.a

all:		$(NAME)

bonus:		$(NAME_B)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDE) -c -g $< -o $@
		
$(NAME):	$(OBJS)
			$(MAKE) -C $(dir $(MLX)) 2> /dev/null
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) $(FRAMEWORK) $(MLX) $(LIB) -o $(NAME) $(OBJS)

$(NAME_B):	$(OBJS_B)
			$(MAKE) -C $(dir $(MLX)) 2> /dev/null
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) $(FRAMEWORK) $(MLX) $(LIB) -o $(NAME_B) $(OBJS_B)

clean:
			$(RM) $(OBJS) $(OBJS:.o=.d)
			$(RM) $(OBJS_B) $(OBJS_B:.o=.d)
			@make -C $(dir $(MLX)) clean
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(MLX)
			$(RM) $(NAME)
			$(RM) $(NAME_B)

re:			fclean all

.PHONY:		all clean fclean re bonus
-include	$(OBJS:.o=.d)
-include	$(OBJS_B:.o=.d)