NAME		= so_long

## COMPILATION
CC			= gcc
# Compilation Flags
CFLAGS		= -g3 -Wall -Wextra -Werror


# Removal Flags. Not sure if necessary
RM			= rm -rf

SRCS		= $(wildcard src/*.c)

OBJS		= $(SRCS:.c=.o)

MINILIBX		= src/libmlx_Darwin.a

$(NAME)	: $(MINILIBX) $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MINILIBX) -lXext -lX11

%.o			: %.c
				$(CC) $(CFLAGS) -c -o $@ $<

$(MINILIBX)	:
				$(MAKE) -C src/minilibx-linux
				# $(MAKE) -C src/minilibx-linux --silent
				cp $(wildcard src/minilibx-linux/libmlx_*.a) $(MINILIBX)

all			: $(NAME)

clean		:
				$(RM) $(OBJS)

fclean		: clean
				$(RM) $(NAME)
				$(RM) $(MINILIBX)
				$(MAKE) -C src/minilibx-linux fclean

re			: fclean $(NAME)

.PHONY		: re fclean clean all