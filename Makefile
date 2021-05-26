NAME		=	cub3D

CC			=	gcc
CFLAG		=	-Wall -Werror -Wextra
#MLFLAG		=	-L/usr/lib -lXext -lX11 -lm -lz

#OS_NAME		=	$(shell uname -s)

#ifeq ($(OS_NAME), Linux)
MINILIB	=	./minilibx-linux/libmlx_Linux.a
MINIDIR =	./minilibx-linux
MLFLAG	=	-L/usr/lib -lXext -lX11 -lm -D LINUX
#endif
#ifeq ($(OS_NAME), Darwin)
#	MINILIB =	./minilibx_mms_20200219/libmlx.dylib
#	MINIDIR =	./minilibx_mms_20200219
#	MLFLAG	=	-framework OpenGL -framework Appkit -D MAC
#endif

SRCS		=	./srcs/main.c\
				./srcs/input/cubstat_input.c\
				./srcs/input/cubstat_check.c\
				./srcs/input/duplicate_check.c\
				./srcs/input/map_input.c\
				./srcs/input/map_check.c\
				./srcs/input/save_input.c\
				./srcs/input/get_next_line/get_next_line.c\
				./srcs/input/get_next_line/get_next_line_utils.c\
				./srcs/game/game_setup.c\
				./srcs/game/game_init.c\
				./srcs/game/load_texture.c\
				./srcs/game/mlx_setup.c\
				./srcs/game/wall_raycast.c\
				./srcs/game/sprite_raycast.c\
				./srcs/game/sprite_calc.c\
				./srcs/game/game_draw.c\
				./srcs/game/game_loop.c\
				./srcs/game/game_key.c\
				./srcs/game/game_save.c\
				./srcs/error/error.c\
				./srcs/error/free.c\


OBJS		=	$(SRCS:.c=.o)
LIBFT		=	./srcs/libft/libft.a
LIBFTDIR	=	./srcs/libft/

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(MAKE) -C $(LIBFTDIR)
				$(MAKE) -C $(MINIDIR)
				$(CC) $(CFLAG) $(OBJS) $(LIBFT) $(MINILIB) $(MLFLAG) -o $(NAME)

clean		:
				rm -f $(OBJS)
				$(MAKE) clean -C $(LIBFTDIR)
				$(MAKE) clean -C $(MINIDIR)

fclean		:	clean
				rm -f $(NAME)
				$(MAKE) fclean -C $(LIBFTDIR)

re			:	fclean all
