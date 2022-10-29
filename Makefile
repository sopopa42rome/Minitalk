# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbardett <mbardett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/14 15:04:21 by mbardett          #+#    #+#              #
#    Updated: 2022/08/14 17:22:05 by mbardett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = server
NAME2 = client

CC = gcc
FLAGS = -Wall -Werror -Wextra

SRCS1 = server.c
SRCS2 = client.c

OBJS1 = $(SRCS1:.c=.o)
OBJS2 = $(SRCS2:.c=.o)

LIBFT = libft/libft.a

%.o: %.c./
	gcc -Wall -Wextra -Werror -c $< -o $@

RM = @rm -f

all: $(NAME1) $(NAME2)
	@echo Minitalk builded.

$(NAME1): $(LIBFT) $(OBJS1)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS1) -o $@
	@echo ciaao

$(NAME2): $(LIBFT) $(OBJS2)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS2) -o $@
	@echo ciaao2

$(LIBFT):
	make -C libft/

clean:
	$(RM) $(OBJS1) $(OBJS2)
	@echo Objects destroyed.

fclean: clean
	$(RM) $(NAME1) $(NAME2)
	@echo Minitalk cleared.

re: fclean
	@make all

.PHONY: all clean fclean re
