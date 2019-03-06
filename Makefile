# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 14:23:06 by twitting          #+#    #+#              #
#    Updated: 2019/03/06 17:36:27 by ebednar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem
SRC = ./src/main.c \
		./src/map_test.c \
		./src/vector_funcs.c \
		./src/engine.c
LIBFT = ./libft/libft.a
OBJECTS = $(SRC:.c=.o)
WWW = -Wall -Wextra -Werror
INCLUDES = -I libft -I includes/ -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers
SDL =  -framework SDL2 -F ~/Library/Frameworks/
FLAGS_LINUX = -I ./includes/  -lXext -lX11 -lm -lpthread -lft

all: $(NAME)

linux:
	make re -C libft/
	sudo gcc $(WWW) $(SRC) $(LIBFT) $(FLAGS_LINUX) -o $(NAME)

$(NAME): $(OBJECTS)
	make -C libft/
	gcc -o $(NAME) $(OBJECTS) $(INCLUDES) $(SDL) $(LIBFT) 

%.o: %.c
	gcc $(WWW) $(INCLUDES) -F ~/Library/Frameworks/ -c $< -o $@ 

clean:
	make clean -C libft/
	/bin/rm -f $(OBJECTS)

fclean: clean
	make fclean -C libft/
	/bin/rm -f $(NAME)

re: fclean all

re_linux: fclean linux