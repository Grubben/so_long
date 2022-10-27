NAME		= so_long

## COMPILATION
CC			= gcc
# Compilation Flags
CFLAGS		= -g3 -Wall -Wextra -Werror


# Removal Flags. Not sure if necessary
RM			= rm -rf

SRCS		= $(wildcard src/*.c)

OBJS		= $(SRCS:.c=.o)

MINILIBX		= src/libmlx_Linux.a
LIBFT			= src/libft.a

$(NAME)	: $(MINILIBX) $(LIBFT) $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MINILIBX) -lXext -lX11

%.o			: %.c
				$(CC) $(CFLAGS) -c -o $@ $<

$(MINILIBX)	:
				$(MAKE) -C src/minilibx-linux
				# $(MAKE) -C src/minilibx-linux --silent
				cp src/minilibx-linux/libmlx_Linux.a $(MINILIBX)

$(LIBFT)	:
				$(MAKE) -C src/libft
				cp src/libft/libft.a $(LIBFT)

all			: $(NAME)

clean		:
				$(RM) $(OBJS)

fclean		: clean
				$(RM) $(NAME)
				$(RM) $(MINILIBX)
				# $(MAKE) -C src/minilibx-linux fclean
				$(RM) $(LIBFT)

re			: fclean $(NAME)

.PHONY		: re fclean clean all
