# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atahiri <atahiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 09:44:00 by atahiri           #+#    #+#              #
#    Updated: 2021/07/05 15:40:54 by atahiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	pipex

all:	$(NAME)

SRCS =	ft_split.c\
		pipex.c\
		ft_substr.c\
		ft_strlen.c\
		ft_strjoin.c\
		ft_strncmp.c\
		get_path.c\
		utils.c\
		ft_strdup.c\
		ft_strchr.c\

OBJS =	$(SRCS:.c=.o)

$(NAME):
	gcc -Wall -Werror -Wextra -c $(SRCS)
	gcc -o $(NAME) $(OBJS)

clean:
	rm -f *.o

fclean:	clean
	rm -f $(NAME)

re:	fclean all