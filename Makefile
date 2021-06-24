# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 09:44:00 by atahiri           #+#    #+#              #
#    Updated: 2021/06/24 09:46:35 by atahiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	pipex

all:	$(NAME)

SRCS =	ft_split.c\
		pipex.c\

OBJS =	$(SRCS:.c=.o)

$(NAME):
	gcc -Wall -Werror -Wextra -c $(SRCS)
	gcc -o $(NAME) $(OBJS) -g

clean:
	rm -f *.o

fclean:	clean
	rm -f $(NAME)

re:	fclean all