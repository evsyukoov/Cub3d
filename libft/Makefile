# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: denis <denis@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/01 15:49:21 by denis             #+#    #+#              #
#    Updated: 2020/05/05 11:55:59 by denis            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
SRC=*.c
INCLUDES=.

all: $(NAME)
	
$(NAME): 
	gcc -Wall -Wextra -Werror -I$(INCLUDES) -c $(SRC)
	ar rc $(NAME) *.o
	ranlib $(NAME)

clean: 
	rm -f *.o

fclean: clean 
	rm -f $(NAME)

re: fclean all
