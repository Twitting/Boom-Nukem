# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twitting <twitting@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 14:23:06 by twitting          #+#    #+#              #
#    Updated: 2019/03/20 18:27:12 by twitting         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = map_editor
SRC = ./main.c \
	./putline.c \
	./initedit.c
LIBFT = ../libft/libft.a
OBJECTS = $(SRC:.c=.o)
WWW = -Wall -Wextra -Werror -Ofast
INCLUDES = -I ../libft -I ../includes/ -I ../includes/frameworks/SDL2.framework/Versions/A/Headers
SDL =  -framework SDL2 -F ../includes/frameworks/
FLAGS_LINUX = -I ../includes/ -lm -lpthread -lSDL2main -lSDL2 -I ../libft

all: $(NAME)

linux:
	make re -C ../libft/
	sudo gcc $(WWW) $(SRC) $(LIBFT) $(FLAGS_LINUX) -o $(NAME)

$(NAME): $(OBJECTS)
	make -C ../libft/
	gcc -o $(NAME) $(OBJECTS) $(INCLUDES) $(SDL) $(LIBFT) 

%.o: %.c
	gcc $(WWW) $(INCLUDES) -F ~/Library/Frameworks/ -c $< -o $@ 

clean:
	make clean -C ../libft/
	/bin/rm -f $(OBJECTS)

fclean: clean
	make fclean -C ../libft/
	/bin/rm -f $(NAME)

re: fclean all

re_linux: fclean linux
