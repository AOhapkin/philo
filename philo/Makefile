# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/01 09:36:32 by gmyriah           #+#    #+#              #
#    Updated: 2022/05/11 17:03:31 by gmyriah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INCLUDES = includes
HEADER = $(INCLUDES)/philo.h

DIR_S = source/
DIR_O = objects/
C_FILES = actions.c init_simulation.c monitioring.c philo.c
SRCS = $(addprefix $(DIR_S),$(C_FILES))
OBJS = $(addprefix $(DIR_O),$(C_FILES:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

.PHONY: all NAME clean fclean re

all: $(DIR_O) $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $@

$(DIR_O)%.o: $(DIR_S)%.c $(HEADER)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(DIR_O):
	mkdir -p $(DIR_O)

clean:
	rm -rf $(DIR_O)

fclean:	clean
	rm -r $(NAME)

re:	fclean all