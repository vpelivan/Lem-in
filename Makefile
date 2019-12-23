#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpelivan <vpelivan@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/06 21:47:58 by vpelivan          #+#    #+#              #
#    Updated: 2019/07/06 22:45:28 by vpelivan         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in

FLAGS = -Wall -Wextra -Werror -I includes/
FLAGS2 = -flto -pipe -Ofast -march=native -mtune=native

LIB = libft/libft.a

SRC = src/main.c\
		src/antwalk.c\
		src/bfs.c\
		src/bfs2.c\
		src/bonuses.c\
		src/bonuses2.c\
		src/copy_add_ways.c\
		src/dpf.c\
		src/dpf2.c\
		src/init_free.c\
		src/lists.c\
		src/parse_ants.c\
		src/parser.c\
		src/parser2.c\
		src/swap.c\
		src/validator.c\
		src/validator2.c\

OBJ = $(SRC:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	@make -C libft/

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(LIB)
	@echo "\033[1;92m lem-in binary created!\033[m"

$(OBJ): %.o: %.c
	@gcc -c $(FLAGS) $(FLAGS2) -o $@ -c $<

clean:
	@make -C libft/ clean
	@rm -f $(OBJ)
	@echo "\033[1;92m project cleaned!\033[m"

fclean: clean
	@rm -rf $(NAME)
	@make -C libft/ fclean
	@echo "\033[1;92m library and binary files deleted!\033[m"

re: fclean all