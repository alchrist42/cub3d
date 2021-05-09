NAME		=	cub3D

SRCS_FILES	= 	main.c \
				parcer.c \
				parcer_map.c \
				parcer_lines.c \
				parcer_utils.c \
				raise_error.c \
				window.c \
				hooks.c \
				img_helpers.c \
				game.c \
				player.c \
				mooving.c \
				gnl/get_next_line.c \
				gnl/get_next_line_utils.c \

SRCS_FOLDER	=	src/
HEADER		=	include/cub3d.h


SRCS		= 	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))
OBJS		=	$(patsubst %.c,%.o,$(SRCS))

INCLUDE		=	-I./include -I./src/libft/ -I./src/gnl/ -I./src/mlx_mms/

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
FRAMEWORK	=	-framework OpenGL -framework AppKit
RM			=	rm -f

LIBC		=	ar rcs

MLX = ./src/mlx_mms/libmlx.dylib
LIB = ./src/libft/libft.a

all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDE) -g -c $< -o $@	
			#todo del -g

$(NAME):	$(OBJS) $(HEADER)
			$(MAKE) -C $(dir $(MLX))
			@mv $(MLX) $(notdir $(MLX))
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(FRAMEWORK) $(INCLUDE) $(notdir $(MLX)) $(LIB) -O3 -o $(NAME) $(OBJS)

bonus:		$(NAME)

libft.a:   

clean:
			$(RM) $(OBJS)
			@make -C $(dir $(MLX)) clean
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(MLX)
			$(RM) $(notdir $(MLX))
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus

