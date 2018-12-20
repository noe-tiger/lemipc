##
## EPITECH PROJECT, 2018
## *
## File description:
## *
##

CC		= gcc
CFLAGS		= -Wall -Werror -Wextra -I./include

RM		= rm -f

NAME		= lemipc

SRCS_DIR	= src/
SRCS_FILES	= main.c
SRCS_FILES	+= init.c
SRCS_FILES	+= game.c
SRCS_FILES	+= bot.c
SRCS_FILES	+= direction.c


SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS		= $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS)
	@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.'

%.o: %.c
	@printf "[\033[0;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.'
	@$(CC) -c -o $@ $< $(CFLAGS)

clean:
	@$(RM) $(OBJS)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(OBJS) | tr ' ' '.'

fclean: clean
	@$(RM) $(NAME)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'

re:	fclean all


.PHONY: all clean fclean re
