NAME		=	cub3D

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

SRCS_FOLDER	=	src/
HEADER		=	include/cub3d.h


SRCS		= 	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))
OBJS		=	$(patsubst %.c,%.o,$(SRCS))

INCLUDE		=	-I./include -I./src/libft/ -I./src/gnl/ -I./src/mlx/

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
FRAMEWORK	=	-framework OpenGL -framework AppKit
RM			=	rm -f

LIBC		=	ar rcs

MLX = ./src/mlx/libmlx.a
LIB = ./src/libft/libft.a

all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@	


$(NAME):	$(OBJS) $(HEADER)
			$(MAKE) -C $(dir $(MLX))
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) $(FRAMEWORK) $(MLX) $(LIB) -o $(NAME) $(OBJS)

bonus:		$(NAME)

clean:
			$(RM) $(OBJS)
			@make -C $(dir $(MLX)) clean
			@make -C $(dir $(LIB)) clean

fclean:		clean
			@make -C $(dir $(LIB)) fclean
			$(RM) $(MLX)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus

