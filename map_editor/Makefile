# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 14:23:06 by twitting          #+#    #+#              #
#    Updated: 2019/04/11 21:25:46 by daharwoo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = map_editor
SRC = ./main.c \
	./putline.c \
	./initedit.c \
	./portals.c \
	./portals_calcs.c \
	./save.c \
	./vertexes.c \
	./buttons.c \
	./save2.c \
	./vertexes_extra.c \
	./vertexes_extra2.c \
	./main_support.c

LIBFT = ../libft/libft.a
OBJECTS = $(SRC:.c=.o)
#WWW = -Wall -Wextra -Werror -Ofast
INCLUDES = -I ../libft -I ../includes/ -I ../includes/frameworks/SDL2.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers -I ../kiss_sdl
SDL =  -F ../includes/frameworks/ -framework SDL2 -framework SDL2_image -framework SDL2_ttf
FLAGS_LINUX =  -I ../includes/ ../kiss_sdl/libkisssdl.a -I ../includes/frameworks/SDL2_ttf.framework/Versions/A/Headers \
 	-I ../includes/frameworks/SDL2_image.framework/Versions/A/Headers \
	 -I ../kiss_sdl  -lm -lpthread -lSDL2main -lSDL2 -I ../libft -lSDL2_ttf -lSDL2_image

all: $(NAME)

linux:
	sudo gcc $(WWW) $(SRC) $(LIBFT) $(FLAGS_LINUX) -o $(NAME)

$(NAME): $(OBJECTS)
	gcc -o $(NAME) $(OBJECTS) $(INCLUDES) $(SDL) $(LIBFT) -L ../kiss_sdl -l kisssdl

%.o: %.c
	gcc $(WWW) $(INCLUDES) -F ~/Library/Frameworks/ -c $< -o $@ 

clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f ./save

re: fclean all

re_linux: fclean linux
