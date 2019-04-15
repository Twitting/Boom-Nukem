# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 14:23:06 by twitting          #+#    #+#              #
#    Updated: 2019/04/15 16:28:16 by ebednar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem
SRC = ./src/main.c \
		./src/parser.c \
		./src/vector_funcs.c \
		./src/engine.c \
		./src/init.c \
		./src/events.c \
		./src/movement.c \
		./src/textures.c \
		./src/scaler.c \
		./src/sprites.c \
		./src/buttons.c \
		./src/shoot.c \
		./src/mobattack.c \
		./src/transparent.c \
		./src/movemob.c \
		./src/walls.c \
		./src/key.c \
		./src/walls2.c \
		./src/wallintersect.c \
		./src/light.c \
		./src/lightswitch.c \
		./src/rotatinglight.c \
		./src/spritedist.c \
		./src/findbutton.c \
		./src/portal.c \
		./src/openbars.c \
		./src/vlines.c \
		./src/walls3.c \
		./src/menu/main.c \
		./src/menu/handle_pause.c \
		./src/menu/handle_menu.c \
		./src/menu/handle_load.c \
		./src/menu/handle_save.c \
		./src/menu/handle_game_mode.c \
		./src/menu/game_over.c \
		./src/menu/menu_pause.c \
		./src/menu/game_mode.c \
		./src/menu/save_game.c \
		./src/menu/load_game.c \
		./src/game_bar/help.c \
		./src/game_bar/key.c \
		./src/game_bar/head.c \
		./src/game_bar/bar.c \
		./src/game_bar/hp.c \
		./src/support1.c \
		./src/support2.c \
		./src/support3.c \
		./src/support4.c \
		./src/support5.c \
		./src/support6.c \
		./src/support7.c

LIBFT = ./libft/libft.a
OBJECTS = $(SRC:.c=.o)
WWW = -Wall -Wextra -Werror -Ofast
INCLUDES = -I libft -I includes/ \
-I includes/frameworks/SDL2.framework/Versions/A/Headers \
-I includes/frameworks/SDL2_image.framework/Versions/A/Headers \
-I includes/frameworks/SDL2_ttf.framework/Versions/A/Headers \
-I includes/frameworks/SDL2_mixer.framework/Versions/A/Headers 
SDL =  -F includes/frameworks/ -framework SDL2 \
-framework SDL2_image \
-framework SDL2_ttf \
-framework SDL2_mixer
FLAGS_LINUX = -I ./includes/ -I includes/frameworks/SDL2.framework/Versions/A/Headers -I \
	includes/frameworks/SDL2_image.framework/Versions/A/Headers -lm -lpthread -lSDL2main -lSDL2 -I libft -lSDL2_image

all: $(NAME)

linux:
	make re -C libft/
	make re -C kiss_sdl/
	make re -C map_editor/
	sudo gcc $(WWW) $(SRC) $(LIBFT) $(FLAGS_LINUX) -o $(NAME)

$(NAME): $(OBJECTS)
	make -C libft/
	make -C map_editor/
	make -C kiss_sdl/
	gcc -o $(NAME) $(OBJECTS) $(INCLUDES) $(SDL) $(LIBFT) 

%.o: %.c
	gcc $(WWW) $(INCLUDES) -c $< -o $@ -F includes/frameworks/

clean:
	make clean -C libft/
	make clean -C map_editor/
	/bin/rm -f $(OBJECTS)

fclean: clean
	make fclean -C libft/
	make fclean -C map_editor/
	/bin/rm -f $(NAME)

re: fclean all

re_linux: fclean linux
